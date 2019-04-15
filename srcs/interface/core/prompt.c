/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 14:49:54 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/12 16:46:02 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"
#include "interface_functions.h"
#include "log.h"
#include "ft_printf.h"

char		*prompt(t_registry *shell_reg, t_interface *itf)
{
	char			character[READ_SIZE + 1];

	ft_bzero(character, READ_SIZE);
	ft_dprintf(STDOUT_FILENO, "\n%s", get_intern_var(shell_reg, itf->state));

	while (character[0] != IFS_CHAR)
	{
		ft_bzero(character, READ_SIZE);
		if (read(0, character, READ_SIZE) == -1)
		{
			//check this
			prompt_read_failed(shell_reg, itf->line);
			return (NULL);
		}
		handle_input_key(character, shell_reg);

		if (is_EOF(itf->line->buffer))
			return (itf->line->buffer);
	}
	tc_ak_end(shell_reg);
	validate_input_quoting(shell_reg, itf);

	// Handle history here

	return (itf->line->buffer);
}
