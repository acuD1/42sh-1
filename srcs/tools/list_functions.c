/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 22:07:09 by cempassi          #+#    #+#             */
/*   Updated: 2019/05/02 03:12:22 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#include "parser.h"

int		find_variable(void *data, void *to_find)
{
	t_variable *variable;
	char		*name;

	name = to_find;
	variable = data;
	return (ft_strequ(variable->name, name));
}

void	delete_process(void *data)
{
	t_process	*process;

	process = (t_process *)data;
	ft_freetab(&process->av);
	ft_freetab(&process->env);
	if (process->fd.in != 0)
		close(process->fd.in);
	if (process->fd.out != 1)
		close(process->fd.out);
	if (process->fd.err != 2)
		close(process->fd.out);
}

void	delete_job(void *data)
{
	t_job	*job;

	job = (t_job *)data;
	ft_lstdel(&job->process_list, delete_process);
}

void	delete_parser(t_parser *parse)
{
	if (parse->tmp_env)
		ft_lstdel(&parse->tmp_env, NULL); //This will leak
	if (parse->job_list)
		ft_lstdel(&parse->job_list, delete_job);
}

char	*variable_to_str(void *data)
{
	char	*string;
	t_variable	*variable;

	variable = data;
	string = NULL;
	ft_asprintf(&string, "%s=%s", variable->name, variable->data);
	return (string);
}
