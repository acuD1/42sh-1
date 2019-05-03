/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 22:07:09 by cempassi          #+#    #+#             */
/*   Updated: 2019/05/03 20:36:44 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include <unistd.h>

void	print_filedesc(t_list *lst)
{
	t_filedesc	*fd;

	fd = lst->data;
	if(fd->action & FD_CLOSE)
		ft_printf("Closing FD : %d\n", fd->first);
	else if (fd->action & FD_WRITE)
		ft_printf("FD : %d >>> FD : %d\n", fd->first, fd->second);
	else if (fd->action & FD_READ)
		ft_printf("FD : %d <<< FD : %d\n", fd->first, fd->second);
}

void	print_process(t_list *node)
{
	t_process	*process;

	process = node->data;
	ft_putchar('\n');
	ft_showtab(process->av);
	ft_lstiter(process->fd, print_filedesc);
}

int		find_variable(void *data, void *to_find)
{
	t_variable *variable;
	char		*name;

	name = to_find;
	variable = data;
	return (ft_strequ(variable->name, name));
}

void	delete_variable(void *data)
{
	t_variable *variable;

	variable = data;
	if (variable->data)
		ft_strdel(&variable->data);
}

void	delete_process(void *data)
{
	t_process	*process;

	process = (t_process *)data;
	ft_freetab(&process->av);
	ft_freetab(&process->env);
	ft_lstdel(&process->fd, NULL);
}

void	delete_job(void *data)
{
	t_job	*job;

	job = (t_job *)data;
	ft_lstdel(&job->process_list, delete_process);
}

void	delete_parser(t_parser *parse)
{
	if (parse->tmp_env != NULL)
		ft_lstdel(&parse->tmp_env, NULL); //This will leak
	if (parse->job_list != NULL)
		ft_lstdel(&parse->job_list, delete_job);
	ft_stckdestroy(&parse->stack, delete_variable);
}

char	*variable_to_str(void *data)
{
	char		*string;
	t_variable	*variable;

	variable = data;
	string = NULL;
	ft_asprintf(&string, "%s=%s", variable->name, variable->data);
	return (string);
}
