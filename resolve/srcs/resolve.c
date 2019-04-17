/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 09:10:32 by nrechati          #+#    #+#             */
/*   Updated: 2019/04/17 16:37:09 by nrechati         ###   ########.fr       */
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


int		check_chevrons(ptr)
{
	if (fd_in != 0)
		dup2(IN, ptr->data->fd_in);
	if (fd_out != 1)
		dup2(OUT, ptr->data->fd_out);
	if (fd_err != 2)
		dup2(ERR, ptr->data->fd_err);
}

int *create_pipe(void)
{
	int fd_pipe[2];

	if (!pipe(fd_pipe))
		return (fd_pipe);
	return (ft_dprintf(2, "[ERROR]: pipe syscall failed\n") & 0);
}

int		exec(t_list *ptr, t_list *head, int pipes[2])
{
	int		p_flag;

	if (pipes)
		dup2( );
	p_flag = 0;
	if (ptr->next)
	{
		pipes = create_pipe();
		p_flag = 1;
	}

	fork()
	{
		if (pid == 0)
		{
			check_chevrons();
			if (p_flag == 1)
				dup2(OUT, pipes[0]);
			if ptr->next != NULL
				exec(ptr->next);
			execve(cmd);
		}
		else
			if (ptr == head)
				waitpid;
	}
}

int 	resolve(t_list **stack, t_registry shell)
{
	t_list *ptr;
	int pipes[2];

	ft_memset(pipes, 0, sizeof(int) * 2);
	ptr = *stack;
	exec(ptr, *stack, NULL);
}
