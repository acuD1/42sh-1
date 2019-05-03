/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 13:13:52 by skuppers          #+#    #+#             */
/*   Updated: 2019/05/03 06:01:08 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "log.h"
#include "sig.h"
#include <unistd.h>

void		redirect(t_list *lst)
{
	t_filedesc *fd;

	fd = lst->data;
	if(fd->action & FD_CLOSE)
		close(fd->second);
	else if (fd->action & FD_WRITE)
		dup2(fd->first, fd->second);
	else if (fd->action & FD_READ)
		dup2(fd->second, fd->first);
}

static char	**str_lst_to_tab(t_list *alst)
{
	int		i;
	size_t	size;
	t_variable	*variable;
	char	*env;
	char	**tabs;

	i = 0;
	size = ft_lstlen(alst);
	if ((tabs = (char **)malloc(sizeof(char *) * (size + 1))) == NULL)
		return (NULL);
	while (alst != NULL)
	{
		variable = (t_variable *)alst->data;
		env = NULL;
		ft_asprintf(&env, "%s=%s", variable->name, variable->data);
		tabs[i] = env;
		alst = alst->next;
		i++;
	}
	tabs[i] = NULL;
	return (tabs);
}
/*
static void	el_redirector(t_filedesc *fd)
{
	if (fd->in != STDIN_FILENO)
	{
		if (fd->in != -1 || close(STDIN_FILENO))
			dup2(fd->in, STDIN_FILENO);
	}
	if (fd->out != STDOUT_FILENO && fd->out != STDIN_FILENO)
	{
		if (fd->out != -1 || close(STDOUT_FILENO))
			dup2(fd->out, STDOUT_FILENO);
	}
	if (fd->err != STDERR_FILENO && fd->err != STDIN_FILENO)
	{
		if (fd->err != -1 || close(STDERR_FILENO))
			dup2(fd->err, STDERR_FILENO);
	}
}
*/

static void	execute_process(t_process *process, t_registry *shell)
{
	char			**environ;

	define_execution_signals(shell);


	////////////////////// DEBUG EXEC ///////////////////////
//	if ((shell->option.option & DEBUG_OPT) != FALSE)
//	{
//		ft_dprintf(2, "\n\x1b[32m[CMD LAUNCH] %s | IN: %d OUT: %d ERR: %d\n\x1b[0m",
//				process->av[0], fd.in, fd.out, fd.err);
//		ft_dprintf(2, "\x1b[35m[OUTPUT]: _______________________\n\x1b[0m\n");
//	}
	/////////////////////////////////////////////////////////

	//el_redirector(&fd);
	ft_lstiter(process->fd, redirect);
	environ = str_lst_to_tab(shell->env);
	/*	Exec the new process	*/
	if (ft_hmap_getdata(&shell->blt_hashmap, process->av[0]) != NULL)
		exit(((t_builtin)ft_hmap_getdata(&shell->blt_hashmap /* HOTFIX */
									, process->av[0]))(shell, process->av));
	else if (ft_hmap_getdata(&shell->bin_hashmap, process->av[0]) != NULL)
		execve(ft_hmap_getdata(&shell->bin_hashmap, process->av[0])
									, process->av, environ);
	else if (process->av[0][0] == '.' || process->av[0][0] == '/')
		execve(process->av[0], process->av, environ);
	////////////////////// DEBUG ERROR ///////////////////////
	ft_dprintf(2, "21sh: command not found: %s\n", process->av[0]);
	//////////////////////////////////////////////////////////

	exit(FAILURE);
}

int8_t		launch_process(t_job *job, t_process *process, t_registry *shell)
{
	pid_t		pid;

	if (ft_hmap_getdata(&shell->blt_hashmap, process->av[0]) != NULL
			&& job->process_list->next == NULL)
		return (((t_builtin)ft_hmap_getdata(&shell->blt_hashmap, process->av[0]))
				(shell, process->av));
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
