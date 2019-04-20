/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 14:49:54 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/20 06:43:37 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#include "interface_functions.h"
#include "log.h"

char		*prompt(t_registry *shell, t_interface *itf)
{
	char			character[READ_SIZE + 1];

	ft_bzero(character, READ_SIZE);
	ft_dprintf(STDOUT_FILENO, "\n%s", get_intern_var(shell, itf->state));
	while (character[0] != IFS_CHAR)
	{
		ft_bzero(character, READ_SIZE);
		if (read(0, character, READ_SIZE) == -1)
		{
			prompt_read_failed(shell, itf->line);
			return (NULL);
		}
		handle_input_key(character, shell);
		if (is_eof(itf->line->buffer))
			return (itf->line->buffer);
	}
	tc_ak_end(shell);
	validate_input_quoting(shell);
	return (itf->line->buffer);
}
