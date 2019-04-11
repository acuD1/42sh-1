/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_registry.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 11:03:36 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/11 18:47:58 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#include "line_edit.h"

void	cleanup_interface(t_interface *itf)
{
	ft_vctreset(itf->line);
	itf->cursor->x = get_prompt_len(itf);
	itf->cursor->y = 0;
	itf->cursor->index = 0;
}

void	free_interface_registry(t_interface *itf)
{
	ft_strdel(&(itf->clip->buffer));
	free(itf->clip);
	ft_strdel(&(itf->termcaps->clear));
	ft_strdel(&(itf->termcaps->begin_insertion));
	ft_strdel(&(itf->termcaps->end_insertion));
	ft_strdel(&(itf->termcaps->cs_down));
	ft_strdel(&(itf->termcaps->cs_up));
	ft_strdel(&(itf->termcaps->cs_right));
	ft_strdel(&(itf->termcaps->cs_left));
	free(itf->termcaps);
	free(itf->window);
	ft_strdel(&(itf->line->buffer));
	free(itf->line);
}
