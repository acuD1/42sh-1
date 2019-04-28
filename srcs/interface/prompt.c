/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 14:49:54 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/27 15:47:20 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface_functions.h"
#include "log.h"
#include "ft_printf.h"
#include "history.h"

char		*prompt(t_registry *shell, t_interface *itf)
{
	char			character[READ_SIZE + 1];

	ft_bzero(character, READ_SIZE);
	ft_dprintf(STDOUT_FILENO, "\n%s", get_intern_var(shell, itf->state));
	itf->hist_ptr = NULL;
	while (character[0] != IFS_CHAR)
	{
		ft_bzero(character, READ_SIZE);
		// change to tty fd
		if (read(0, character, READ_SIZE) == -1)
		{
			prompt_read_failed(shell, itf->line);
			return (NULL);
		}
		handle_input_key(shell, character);
		if (is_eof(itf->line->buffer))
			return (itf->line->buffer);
	}
	tc_ak_end(shell);
	validate_input_quoting(shell, itf);
	return (itf->line->buffer);
}
