/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_clip_copy_ak.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 10:40:38 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/15 13:30:38 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"
#include "ft_printf.h"
#include "log.h"
#include "interface_functions.h"

int8_t	tc_ak_copy_before_cursor(t_registry *shell)
{
	t_interface	*itf;

	itf = shell->interface;
	if (validate_interface_content(itf) != 0)
		return (-1);
	realloc_vector(itf->clip, itf->line);
	itf->clip->buffer = ft_strncpy(itf->clip->buffer,
					itf->line->buffer, itf->cursor->index);

log_print(shell, LOG_INFO, "Copied |%s| to clipboard.\n", itf->clip->buffer);
	return (0);
}

int8_t	tc_ak_copy_after_cursor(t_registry *shell)
{
	char	*tmp;
	t_interface	*itf;

	itf = shell->interface;
	if (validate_interface_content(itf) != 0)
		return (-1);
	realloc_vector(itf->clip, itf->line);
	tmp = ft_strsub(itf->line->buffer,
			itf->cursor->index, ft_vctlen(itf->line));
	itf->clip->buffer = ft_strcpy(itf->clip->buffer, tmp);
	ft_strdel(&tmp);

log_print(shell, LOG_INFO, "Copied |%s| to clipboard.\n", itf->clip->buffer);
	return (0);
}

int8_t	tc_ak_copy_line(t_registry *shell)
{
	t_interface	*itf;

	itf = shell->interface;
	if (validate_interface_content(itf) != 0)
		return (-1);
	realloc_vector(itf->clip, itf->line);
	ft_strcpy(itf->clip->buffer, itf->line->buffer);

log_print(shell, LOG_INFO, "Copied |%s| to clipboard.\n", itf->clip->buffer);
	return (0);
}
