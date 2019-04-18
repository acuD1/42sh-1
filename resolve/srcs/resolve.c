/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 09:10:32 by nrechati          #+#    #+#             */
/*   Updated: 2019/04/18 15:12:53 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "resolve.h"
#include "21sh.h"
/*
int		resolve_stack(t_list **stack, t_registry *shell)
{
	void	*data;
	t_list	*ptr;

	ptr = *stack;
	while (ptr)
	{
		if ((data = ft_hmap_getdata(&shell->bin_hashmap, ((t_instr *)ptr->data)->av[0])))
			data();
		if ((data = ft_hmap_getdata(&shell->bin_hashmap, ((t_instr *)ptr->data)->av[0])))
			exec_bin;

		execve(data, ((t_instr *)ptr->data)->av, ((t_instr *)ptr->data)->env);
		ptr = ptr->next;
	}
	return (1);
}
*/


int		check_chevrons(t_list *ptr)
{
	if (((t_instr*)ptr->data)->fd_in != 0)
	{
		dup2(((t_instr *)ptr->data)->fd_in, STDIN_FILENO);
		return (1);
	}
	if (((t_instr*)ptr->data)->fd_out != 1)
	{
		dup2(((t_instr*)ptr->data)->fd_out, STDOUT_FILENO);
		return (1);
	}
	if (((t_instr*)ptr->data)->fd_err != 2)
	{
		dup2(((t_instr *)ptr->data)->fd_err, STDERR_FILENO);
		return (1);
	}
	return (0);
}

int *create_pipe(void)
{
	int *fd_pipe;

	fd_pipe = malloc(sizeof(int) * 2);
	if (!pipe(fd_pipe))
		return (fd_pipe);
	ft_dprintf(2, "[ERROR]: pipe syscall failed\n");
	return (NULL);
}

static int		exec(t_list *ptr, t_list *head, t_registry *shell,int pipes[2])
{
	pid_t	pid;
	int		p_flag;
	int		r_flag;
	int		status;

	if (pipes)
		dup2(STDIN_FILENO, pipes[1]);
	p_flag = 0;
	if (ptr->next)
	{
		pipes = create_pipe();
		p_flag = 1;
	}

	// Set signal behavior
	if ((pid = fork()) == -1)
	{
			//erro
	}
	if (pid == 0)
	{
		r_flag = check_chevrons(ptr);
		if (p_flag == 1)
			dup2(STDOUT_FILENO, pipes[0]);

		if (ptr->next)
			exec(ptr->next, head, shell, pipes);

		if (!ft_hmap_getdata(&shell->bin_hashmap,((t_instr*)ptr->data)->av[0]))
			return (ft_dprintf(2, "\n\x1b[31m[ERROR]: Binary \x1b[93m%s\x1b[31m not found !\n\x1b[0m"
			, ((t_instr *)ptr->data)->av[0]));
		execve(ft_hmap_getdata(&shell->bin_hashmap,((t_instr*)ptr->data)->av[0]),
						((t_instr*)ptr->data)->av,
						((t_instr*)ptr->data)->env);
		close(((t_instr*)ptr->data)->fd_out);
		// Closedir if redirect;
	}
	else if (ptr == head)
	{
		ft_dprintf(2, "\n\x1b[32m[FORKING]: Parent is Waiting ...\n\x1b[0m");
		waitpid(pid, &status, 0);
	}
	//restore signals
	return (0);
}

int 	resolve_stack(t_list **stack, t_registry *shell)
{
	t_list *ptr;
	int pipes[2];

	ft_memset(pipes, 0, sizeof(int) * 2);
	ptr = *stack;
	exec(ptr, *stack, shell, NULL);
	return (0);
}
