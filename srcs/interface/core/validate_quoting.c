/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_quoting.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 15:54:16 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/11 17:59:15 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"
#include "log.h"

static void		set_ifs_char(t_interface *itf)
{
	itf->cursor->index = tc_ak_end(itf);
	itf->line->buffer[itf->cursor->index] = IFS_CHAR;
	itf->cursor->index++;
}

static void		prepare_for_ps2(t_interface *itf)
{
	if (itf->cursor->index > itf->line->size - 2)
		ft_vctrescale(itf->line);
	set_ifs_char(itf);
	itf->interface_state = INT_PS2;
}

int32_t		goto_next_quote(char *string, char quote, uint32_t index)
{
	uint32_t		found_match;

	found_match = index;
	while (string[found_match] != '\0' && string[found_match] != quote)
		++found_match;
	if (string[found_match] == quote)
		return (found_match);
	return (-1);
}

static void		call_ps2_prompt(t_registry *sh_reg, t_interface *itf_reg)
{
	if (invoke_ps2_prompt(sh_reg, itf_reg) != 0)
		log_print(sh_reg, LOG_ERROR, "PS2 prompt failed1\n");
	else
		validate_input_quoting(sh_reg, itf_reg);
}

void			validate_input_quoting(t_registry *sh_reg, t_interface *itf_reg)
{
	int32_t			index;
	int32_t		length;
	char			*string;
	char			quote;

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
