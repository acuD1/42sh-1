/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_registry.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 11:03:36 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/20 01:02:38 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#include "line_edit.h"
#include "interface_functions.h"

void	cleanup_interface(t_registry *shell)
{
	ft_vctreset(shell->interface.line);
	shell->interface.cursor->x = get_prompt_len(shell);
	shell->interface.cursor->y = 0;
	shell->interface.cursor->index = 0;
}

void	free_interface_registry(t_interface *itf)
{
	ft_strdel(&(itf->clip->buffer));
	free(itf->clip);
	ft_strdel(&(itf->line->buffer));
	free(itf->line);
	ft_strdel(&(itf->termcaps->clear));
	ft_strdel(&(itf->termcaps->cs_down));
	ft_strdel(&(itf->termcaps->cs_up));
	ft_strdel(&(itf->termcaps->cs_right));
	ft_strdel(&(itf->termcaps->cs_left));
	free(itf->termcaps);
	free(itf->window);
	free(itf->cursor);
}
