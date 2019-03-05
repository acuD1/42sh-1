/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 16:28:35 by skuppers          #+#    #+#             */
/*   Updated: 2019/03/05 14:57:36 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "21sh.h"
#include "line_edit.h"
#include "log.h"

int		character_is_escaped(char *str, size_t index)
{
	if (index == 0)
		return (0);
	else if (index == ft_strlen(str)) //newline is escaped
	{
		if (str[index - 1] == '\\')
			return (1);
	}
	else
	{
		if (str[index - 1] == '\\')
			return (1);
	}
	return (0);
}

int		goto_simple_quote(char *string, size_t index)
{
	int		found_matching_quote;

	found_matching_quote = index;
	while (string[found_matching_quote] != '\0' &&
			string[found_matching_quote] != '\'')
		++found_matching_quote;
	if (string[found_matching_quote] == '\'')
		return (found_matching_quote);
	return (-1);
}

int		goto_double_quote(char *string, size_t index)
{
	int		found_matching_quote;

	found_matching_quote = index;
	while (string[found_matching_quote] != '\0' &&
			string[found_matching_quote] != '\"')
		++found_matching_quote;
	if (string[found_matching_quote] == '\"')
		return (found_matching_quote);
	return (-1);
}

//TODO: handle escape sequences
// `\` preserves the litteral value of any character except `\n`
//

void	validate_input_quoting(t_registry *sh_reg,
		t_interface_registry *itf_reg)
{
	int			index;
	int			length;
	char		*string;

	index = 0;
	string = itf_reg->vector->buffer;
	length = (int)ft_strlen(string);
	while (index < length && string[index] != '\0')
	{
		if (string[index] == '\\')
		{
			log_print(sh_reg, LOG_INFO, "Found an escape sequence:\n");
			++index;
			if (index < length && string[index] == '\'')
			{
				log_print(sh_reg, LOG_INFO, "\t - Simple quote.\n");
			}
			else if (index < length && string[index] == '\"')
			{
				log_print(sh_reg, LOG_INFO, "\t - Double quote.\n");
			}
			else if (index < length && string[index] == '\\')
			{
				log_print(sh_reg, LOG_INFO, "\t - Backslash.\n");
			}
			else if (index == length)
			{
				log_print(sh_reg, LOG_INFO, "\t - Newline.\n");
				string[index - 1] = '\0';
				if (invoke_ps2_prompt(sh_reg, itf_reg) != 0)
						log_print(sh_reg, LOG_ERROR, "PS2 prompt failed!\n");
					else
					{
						log_print(sh_reg, LOG_INFO, "Joined: |%s|\n", itf_reg->vector->buffer);
						validate_input_quoting(sh_reg, itf_reg);
					}

			}
			else
			{
				log_print(sh_reg, LOG_INFO, "\t - Character: |%c|.\n",string[index]);
			}
		}
		else if (string[index] == '\'' || string[index] == '\"')
		{
			if (string[index] == '\'')
			{
				log_print(sh_reg, LOG_INFO, "Simple quote.\n");
				if (goto_simple_quote(string, index + 1) == -1)
				{
					log_print(sh_reg, LOG_INFO, "Incomplete single quoting.\n");
					itf_reg->vector->buffer[itf_reg->window->cursor_index] =
						IFS_CHARACTER;
					invoke_ps2_prompt(sh_reg, itf_reg);
					log_print(sh_reg, LOG_INFO, "Joined: |%s|\n", itf_reg->vector->buffer);
				}
				else
				{
					log_print(sh_reg, LOG_INFO, "Complete single quoting\n");
					index = goto_simple_quote(string, index + 1);
				}
			}
			else
			{
				log_print(sh_reg, LOG_INFO, "Double quote.\n");
				if (goto_double_quote(string, index + 1) == -1)
				{
					log_print(sh_reg, LOG_INFO, "Incomplete double quoting.\n");

					if (itf_reg->window->cursor_index > (int)itf_reg->vector->size - 2)
						ft_vctrescale(itf_reg->vector);
					itf_reg->window->cursor_index = tc_ak_end(itf_reg);
					itf_reg->vector->buffer[itf_reg->window->cursor_index] =
						'X';
					itf_reg->window->cursor_index++;

					if (invoke_ps2_prompt(sh_reg, itf_reg) != 0)
						log_print(sh_reg, LOG_ERROR, "PS2 prompt failed1\n");
					else
					{
						log_print(sh_reg, LOG_INFO, "Joined: |%s|\n", itf_reg->vector->buffer);
						validate_input_quoting(sh_reg, itf_reg);
					}
				}
				else
				{
					log_print(sh_reg, LOG_INFO, "Complete double quoting\n");
					index = goto_double_quote(string, index + 1);

				}
			}
		}
		++index;
	}
}
