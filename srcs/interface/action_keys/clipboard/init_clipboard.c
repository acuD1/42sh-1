/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_clipboard.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 00:17:19 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/27 15:57:29 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "log.h"

/*
**		Initialise the clipboard vector.
*/

t_vector	*allocate_clipboard(t_registry *shell)
{
	t_vector		*clipboard;

	if ((clipboard = ft_vctnew(CLIPBOARD_SZ)) == NULL)
	{
		log_print(shell, LOG_ERROR, "Clipboard allocation failed.\n");
		return (NULL);
	}
	return (clipboard);
}
