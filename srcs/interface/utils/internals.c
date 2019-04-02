/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   internals.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 17:15:49 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/02 18:48:13 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "log.h"
#include "line_edit.h"

int		add_internal(t_registry *reg, char *name, char *data)
{
	if (get_data(&(reg->intern), name) == NULL)
		return (s_create_node(&(reg->intern), name, data));
	return (change_node(&(reg->intern), name, data));
}

char	*get_intern_var(t_registry *reg, char *name)
{
	return (get_data(&(reg->intern), name));
}

char	*get_itf_intern_var(t_interface_registry *reg, char *name)
{
	return (get_data(&(reg->intern), name));
}
