/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_clipboard.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 00:17:19 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/12 15:56:54 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "log.h"
#include "line_edit.h"

/*
**		Initialise the clipboard vector.
*/

t_vector	*allocate_clipboard(t_registry *sh_reg)
{
	t_vector		*clipboard;

	if ((clipboard = ft_vctnew(CLIPBOARD_SZ)) == NULL)
	{
		log_print(sh_reg, LOG_ERROR, "Clipboard allocation failed.\n");
		return (NULL);
	}
	return (clipboard);
}
