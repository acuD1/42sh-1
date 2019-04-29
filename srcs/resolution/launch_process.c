/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 13:13:52 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/29 16:35:39 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#include "log.h"
#include "resolve.h"

char		**str_lst_to_tab(t_list *alst)
{
	int		i;
	size_t	size;
	t_node	*data;
	char	*env;
	char	**tabs;

	i = 0;
	size = ft_lstlen(alst);
	if ((tabs = (char **)malloc(sizeof(char *) * (size + 1))) == NULL)
		return (NULL);
	while (alst != NULL)
	{
		data = (t_node *)alst->data;
		env = NULL;
		ft_asprintf(&env, "%s=%s", data->var, data->data);
		tabs[i] = env;
		alst = alst->next;
		i++;
	}
	tabs[i] = NULL;
	return (tabs);
}

static void	el_redirector(t_filedesc *fd, char *name)
{
	ft_printf("%s || IN = %d || OUT = %d || ERR = %d\n", name, fd->in, fd->out, fd->err);
	if (fd->in != STDIN_FILENO)
	{
		if (fd->in != -1 || close(STDIN_FILENO))
			ft_printf("%s || STDIN_FILENO duped to %d\n", name,fd->in);
			dup2(fd->in, STDIN_FILENO);
	}
	if (fd->out != STDOUT_FILENO && fd->out != STDIN_FILENO)
	{
		if (fd->out != -1 || close(STDOUT_FILENO))
			ft_printf("%s || STDOUT_FILENO duped to %d\n", name, fd->out);
			dup2(fd->out, STDOUT_FILENO);
	}
	if (fd->err != STDERR_FILENO && fd->err != STDIN_FILENO)
	{
		if (fd->err != -1 || close(STDERR_FILENO))
			ft_printf("%s || STDERR_FILENO duped to %d\n", name, fd->err);
			dup2(fd->err, STDERR_FILENO);
	}
}

static void	execute_process(t_process *process, t_registry *shell)
{
	char			**environ;
	t_filedesc		fd;
	fd = process->fd;
	signal(SIGINT, SIG_DFL); // way more
	ft_dprintf(2, "\x1b[32m[CMD LAUNCH] %s | IN: %d OUT: %d ERR: %d\n\x1b[0m",
				process->av[0], fd.in, fd.out, fd.err);
	ft_dprintf(2, "\x1b[35m[OUTPUT]: _______________________\n\x1b[0m");
	el_redirector(&fd, process->av[0]);
	environ = str_lst_to_tab(shell->env);
	/*	Exec the new process	*/
	if (ft_hmap_getdata(&shell->blt_hashmap, process->av[0]) != NULL)
		((t_builtin)ft_hmap_getdata(&shell->blt_hashmap
									, process->av[0]))(shell, process->av);
	else if (ft_hmap_getdata(&shell->bin_hashmap, process->av[0]) != NULL)
		execve(ft_hmap_getdata(&shell->bin_hashmap, process->av[0])
									, process->av, environ);
	else
		execve(process->av[0], process->av, environ);
	ft_dprintf(2, "[ERROR] - Execution failed: %s.\n", process->av[0]);
	exit(FAILURE);
}

int		launch_process(t_job *job, t_process *process, t_registry *shell)
{
	pid_t		pid;

	if (ft_hmap_getdata(&shell->blt_hashmap, process->av[0]) != NULL
			&& job->process_list->next == NULL)
	{
		((t_builtin)ft_hmap_getdata(&shell->blt_hashmap, process->av[0]))
													(shell, process->av);
		return (FAILURE);
	}
	else
	{
		pid = fork();
		if (pid == 0)
			execute_process(process, shell);
		else if (pid < 0)
		{
			ft_dprintf(2, "[ERROR]: Fork() failed.\n");
			exit(FAILURE);
		}
		else
		{
			process->pid = pid;
			if (job->pgid == 0)
				job->pgid = pid;
		}
	}
	return (SUCCESS);
}
