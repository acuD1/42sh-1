/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_registry.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 16:13:47 by skuppers          #+#    #+#             */
/*   Updated: 2019/03/06 16:13:50 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#include "line_edit.h"

void	cleanup_interface_registry(t_interface_registry *itf_reg)
{

	//ft_strdel(&(itf_reg->clipboard->buffer));
	//free(itf_reg->clipboard);
	ft_strdel(&(itf_reg->vector->buffer));
	free(itf_reg->vector);

	free(itf_reg->window);

}
