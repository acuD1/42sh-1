/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_quoting.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 15:54:16 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/09 19:12:26 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"
#include "log.h"

static void		set_ifs_char(t_interface_registry *itf_reg)
{
	char ifs_char;

	ifs_char = ft_atoi(get_intern_var(itf_reg->sh_reg, INT_IFS));
	itf_reg->window->cursor = tc_ak_end(itf_reg);
	itf_reg->line->buffer[itf_reg->window->cursor] = ifs_char;
	itf_reg->window->cursor++;
}

static void		prepare_for_ps2(t_interface_registry *itf_reg)
{
	if (itf_reg->window->cursor
			> itf_reg->line->size - 2)
		ft_vctrescale(itf_reg->line);
	set_ifs_char(itf_reg);
	itf_reg->interface_state = INT_PS2;
}

int				goto_next_quote(char *string, char quote, size_t index)
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

static void		call_ps2_prompt(t_registry *sh_reg,
				t_interface_registry *itf_reg)
{
	if (invoke_ps2_prompt(sh_reg, itf_reg) != 0)
		log_print(sh_reg, LOG_ERROR, "PS2 prompt failed1\n");
	else
		validate_input_quoting(sh_reg, itf_reg);
}

void			validate_input_quoting(t_registry *sh_reg,
		t_interface_registry *itf_reg)
{
	int			index;
	int			length;
	char		*string;
	char		quote;

	index = -1;
	quote = 0;
	string = itf_reg->line->buffer;
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
				itf_reg->interface_state = INT_PS1;
				return ;
			}
			else
				index = goto_next_quote(string, quote, index + 1);
		}
	}
}
