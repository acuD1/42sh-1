/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   internals.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 17:15:49 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/03 12:53:22 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "log.h"
#include "line_edit.h"

char	*get_intern_var(t_registry *reg, char *name)
{
	return (get_data(&(reg->intern), name));
}

int		add_internal(t_registry *reg, char *name, char *data)
{
	if (get_data(&(reg->intern), name) == NULL)
		return (s_create_node(&(reg->intern), name, data));
	return (change_node(&(reg->intern), name, ft_strdup(data)));
}

int		add_internal_nbr(t_registry *reg, char *name, int data)
{
	int		success;
	char	*data_copy;

	success = 0;
	data_copy = NULL;
	data_copy = ft_itoa(data);
	success = add_internal(reg, name, data_copy);
	ft_strdel(&data_copy);
	return (success);
}
