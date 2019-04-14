/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_registry.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 11:03:36 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/12 16:28:48 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#include "line_edit.h"
#include "interface_functions.h"

void	cleanup_interface(t_registry *shell)
{
	ft_vctreset(shell->interface->line);
	shell->interface->cursor->x = get_prompt_len(shell);
	shell->interface->cursor->y = 0;
	shell->interface->cursor->index = 0;
}

void	free_interface_registry(t_interface *itf)
{
	ft_strdel(&(itf->clip->buffer));
	free(itf->clip);

	ft_strdel(&(itf->termcaps->clear));
	ft_strdel(&(itf->termcaps->cs_down));
	ft_strdel(&(itf->termcaps->cs_up));
	ft_strdel(&(itf->termcaps->cs_right));
	ft_strdel(&(itf->termcaps->cs_left));
	free(itf->termcaps);

	free(itf->window);
	ft_strdel(&(itf->line->buffer));
	free(itf->line);
}

void	reset_vector(t_vector *line)
{
	free(line->buffer);
	line->buffer = ft_strnew(16);
	line->size = 16;
}

void	replace_vetor(t_vector *dest, t_vector *src)
{
	ft_strdel(&(dest->buffer));
	dest->buffer = ft_strdup(src->buffer);
	dest->size = ft_strlen(src->buffer);
	ft_strdel(&(src->buffer));
	free(src);
}

void	move_vector(t_vector *dest, char *src)
{
	ft_strdel(&(dest->buffer));
	dest->buffer = ft_strdup(src);
	dest->size = ft_strlen(src);
	free(src);
}
