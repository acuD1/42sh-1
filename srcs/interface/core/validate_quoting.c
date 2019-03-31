/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_quoting.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 15:54:16 by skuppers          #+#    #+#             */
/*   Updated: 2019/03/31 18:04:18 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#include "line_edit.h"
#include "log.h"

static char set_quote(char c)
{
	if (c == '\'' || c == '\"' || c == '`')
		return (c);
	return (0);
}

static void set_ifs_char(t_interface_registry *itf_reg)
{
	itf_reg->window->cursor_index = tc_ak_end(itf_reg);
	itf_reg->vector->buffer[itf_reg->window->cursor_index]
		 = IFS_CHARACTER;
	itf_reg->window->cursor_index++;
}

static void prepare_for_ps2(t_interface_registry *itf_reg)
{
	if (itf_reg->window->cursor_index
			> (int)itf_reg->vector->size - 2)
		ft_vctrescale(itf_reg->vector);
	set_ifs_char(itf_reg);
	itf_reg->interface_state = PS2;
}

int		goto_next_quote(char *string, char quote, size_t index)
{
	int		found_matching_quote;

	found_matching_quote = index;
	while (string[found_matching_quote] != '\0' &&
			string[found_matching_quote] != quote)
		++found_matching_quote;
	if (string[found_matching_quote] == quote)
		return (found_matching_quote);
	return (-1);
}

static void call_ps2_prompt(t_registry *sh_reg, t_interface_registry *itf_reg)
{
	if (invoke_ps2_prompt(sh_reg, itf_reg) != 0)
		log_print(sh_reg, LOG_ERROR, "PS2 prompt failed1\n");
	else
		validate_input_quoting(sh_reg, itf_reg);
}

void	validate_input_quoting(t_registry *sh_reg,
		t_interface_registry *itf_reg)
{
	int			index;
	int			length;
	char		*string;
	char		quote;

	index = -1;
	quote = 0;
	string = itf_reg->vector->buffer;
	length = (int)ft_strlen(string);
	while (index < length && string[++index] != '\0')
	{
		quote = set_quote(string[index]);
		if (quote != 0)
		{
			if (goto_next_quote(string, quote, index + 1) == -1)
			{
				prepare_for_ps2(itf_reg);
				call_ps2_prompt(sh_reg, itf_reg);
				itf_reg->interface_state = PS1;
				return ;
			}
			else
				index = goto_next_quote(string, quote, index + 1);
		}
	}
}
