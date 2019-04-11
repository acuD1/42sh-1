/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 14:49:54 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/11 18:14:27 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"
#include "log.h"
#include "ft_printf.h"

uint8_t	is_EOF(char *buffer)
{
	if (buffer[0] == 4 && buffer[1] == '\0')
		return (1);
	return (0);
}

char		*prompt(t_registry *shell_reg,
				t_interface *itf)
{
	char			character[READ_SIZE + 1];

	ft_bzero(character, READ_SIZE);
	ft_dprintf(STDOUT_FILENO, "\n%s", get_intern_var(shell_reg, INT_PS1));

	while (character[0] != IFS_CHAR)
	{
		ft_bzero(character, READ_SIZE);
		if (read(0, character, READ_SIZE) == -1)
		{
			prompt_read_failed(shell_reg, itf->line);
			return (NULL);
		}
		handle_input_key(character, itf);

		if (is_EOF(itf->line->buffer))
			return (itf->line->buffer);
	}
	tc_ak_end(itf);
	validate_input_quoting(shell_reg, itf);

	// Handle history here

	return (itf->line->buffer);
}
