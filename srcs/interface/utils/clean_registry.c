/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_registry.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 11:03:36 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/09 19:13:38 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#include "line_edit.h"

void	cleanup_interface_registry(t_interface_registry *itf_reg)
{
	//ft_strdel(&(itf_reg->clip->buffer));
	//free(itf_reg->clip);
	ft_strdel(&(itf_reg->line->buffer));
	free(itf_reg->line);
	free(itf_reg->window);
	//free(itf_reg->window);
}

void	free_interface_registry(t_interface_registry *itf_reg)
{
	ft_strdel(&(itf_reg->clip->buffer));
	free(itf_reg->clip);
	ft_strdel(&(itf_reg->termcaps->clear));
	ft_strdel(&(itf_reg->termcaps->begin_insertion));
	ft_strdel(&(itf_reg->termcaps->end_insertion));
	ft_strdel(&(itf_reg->termcaps->cs_down));
	ft_strdel(&(itf_reg->termcaps->cs_up));
	ft_strdel(&(itf_reg->termcaps->cs_right));
	ft_strdel(&(itf_reg->termcaps->cs_left));
	free(itf_reg->termcaps);
	free(itf_reg->window);
	ft_strdel(&(itf_reg->line->buffer));
	free(itf_reg->line);
}
