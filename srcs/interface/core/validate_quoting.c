/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_quoting.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 15:54:16 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/12 16:28:09 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"
#include "interface_functions.h"
#include "log.h"

static int32_t		goto_next_quote(char *string, char quote, uint32_t index)
{
	uint32_t		found_match;

	found_match = index;
	while (string[found_match] != '\0' && string[found_match] != quote)
		++found_match;
	if (string[found_match] == quote)
		return (found_match);
	return (-1);
}

int8_t	quoting_is_valid(char *str)
{
	int32_t		length;
	int32_t		index;
	char		quote;

	quote = 0;
	index = 0;
	length = ft_strlen(str);
	while (index < length && str[index] != '\0')
	{
		quote = set_quote(str[index]);
		if (quote != 0)
		{
			if (goto_next_quote(str, quote, index + 1) != -1)
				index = goto_next_quote(str, quote, index + 1);
			else
				return (-1);
		}
		++index;
	}
	return (1);
}

void			validate_input_quoting(t_registry *shell, t_interface *itf)
{
	if (quoting_is_valid(itf->line->buffer) == -1)
		invoke_sub_prompt(shell, quoting_is_valid, INT_PS1, INT_PS2);
}
