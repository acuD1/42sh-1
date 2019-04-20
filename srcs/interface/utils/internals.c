/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   internals.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 17:15:49 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/20 04:14:52 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"
#include "log.h"

char	*get_intern_var(t_registry *reg, char *name)
{
	return (get_data((reg->intern), name));
}

int		add_internal(t_registry *reg, char *name, char *data)
{
	if (get_data(reg->intern, name) == NULL)
		return (s_create_node(&(reg->intern), name, data));
	return (change_node(&(reg->intern), name, ft_strdup(data)));
}

int		add_internal_nbr(t_registry *reg, char *name, int data)
{
	int		success;
	char	*data_copy;

	data_copy = ft_itoa(data);
	success = change_node(&reg->intern, name, data_copy);
	ft_strdel(&data_copy);
	return (success);
}
