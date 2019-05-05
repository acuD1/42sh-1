/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 13:13:52 by skuppers          #+#    #+#             */
/*   Updated: 2019/05/05 05:42:30 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "log.h"
#include "sig.h"
#include <unistd.h>
#include <fcntl.h>

void		redirect(void *data)
{
	t_filedesc *fd;

	fd = data;
	if (fd->action & FD_CLOSE)
		close(fd->second);
	else if (fd->action & FD_WRITE)
		dup2(fd->first, fd->second);
	else if (fd->action & FD_READ)
		dup2(fd->second, fd->first);
}

static char	**str_lst_to_tab(t_list *alst)
{
	uint32_t	i;
	size_t		size;
	t_variable	*variable;
	char		*env;
	char		**tabs;

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

static void	execute_process(t_process *process, t_registry *shell, char **env)
{

	define_execution_signals();
	ft_lstiter(process->fd, redirect);
	if (ft_hmap_getdata(&shell->blt_hashmap, process->av[0]) != NULL)
		exit(((t_builtin)ft_hmap_getdata(&shell->blt_hashmap /* HOTFIX */
						, process->av[0]))(shell, process->av));
	else if (ft_hmap_getdata(&shell->bin_hashmap, process->av[0]) != NULL)
		execve(ft_hmap_getdata(&shell->bin_hashmap, process->av[0])
				, process->av, env);
	else if (process->av[0][0] == '.' || process->av[0][0] == '/')
		execve(process->av[0], process->av, env);
	ft_dprintf(2, "21sh: command not found: %s\n", process->av[0]);
	exit(FAILURE);
}

int			launch_builtin(t_registry *shell, t_process *process)
{
	t_builtin		f;
	t_filedesc 		*fd;
	int				tmp_fd;

	if (!(f = ft_hmap_getdata(&shell->blt_hashmap, process->av[0])))
		return (FALSE);
	if (!process->fd || !(fd = (t_filedesc *)(process->fd->data)))
	{
		f(shell, process->av);
		return (1);
	}
	tmp_fd = fcntl(fd->second, F_DUPFD, 10);
	fcntl(tmp_fd, F_SETFD, FD_CLOEXEC);
	if (fd->action & FD_WRITE)
	{
		dup2(fd->first, fd->second);
		close(fd->second);
	//	if (fd->action & FD_CLOSE)
	//		close(fd->first);
		f(shell, process->av);
		dup2(tmp_fd, fd->second);
		close(tmp_fd);
	}
	return (0);
}

int8_t		launch_process(t_job *job, t_process *process, t_registry *shell)
{
	pid_t		pid;
	char		**env;

	if (process->av == NULL)
		return (SUCCESS);
	env = str_lst_to_tab(shell->env);
	if (job->process_list->next == NULL && launch_builtin(shell, process))
		return (SUCCESS);
	if ((pid = fork()) == SUCCESS)
		execute_process(process, shell, env);
	else if (pid < 0)
	{
		ft_dprintf(2, "[ERROR]: Fork() failed.\n");
		return (FAILURE);
	}
	ft_freetab(&env);
	process->pid = pid;
	job->pgid = job->pgid ? job->pgid  :pid;
	return (SUCCESS);
}
