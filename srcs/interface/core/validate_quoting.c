/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_quoting.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 15:54:16 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/23 19:34:29 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"
#include "interface_functions.h"
#include "log.h"

static int32_t	goto_next_quote(char *string, char quote, uint32_t index)
{
	uint32_t		found_match;

	found_match = index;
	while (string[found_match] != '\0' && string[found_match] != quote)
		++found_match;
	if (string[found_match] == quote)
		return (found_match);
	return (-1);
}

int8_t			quoting_is_valid(char *str)
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
	char	*line;
	char	*tmp_line;
	char	*final_line;
	char	*save_state;

	save_state = itf->state;
	while (quoting_is_valid(itf->line->buffer) == -1)
	{
		final_line = NULL;
		tmp_line = ft_strdup(itf->line->buffer);

		invoke_sub_prompt(shell, &line, INT_PS2);
		ft_asprintf(&final_line, "%s%c%s", tmp_line, IFS_CHAR, line);
		ft_strdel(&line);
		line = NULL;
		ft_strdel(&tmp_line);
		tmp_line = NULL;
		itf->line->buffer = ft_strdup(final_line);
		itf->line->size = ft_strlen(itf->line->buffer);
		ft_strdel(&final_line);
		final_line = NULL;
		log_print(shell, LOG_INFO,
						"Sub-prompt concat:|%s|\n", itf->line->buffer);
	}
	itf->state = save_state;
}
