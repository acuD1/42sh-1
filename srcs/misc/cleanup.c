/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 16:28:35 by skuppers          #+#    #+#             */
/*   Updated: 2019/03/04 17:24:17 by skuppers         ###   ########.fr       */
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

int		parse_simple_quotes(char *string)
{
	(void)string;
	return (0);
}

int		parse_double_quotes(char *string)
{
	(void)string;
	return (0);
}

//TODO: handle escape sequences
// `\` preserves the litteral value of any character except `\n`
//

void	validate_input_quoting(t_registry *sh_reg,
		t_interface_registry *itf_reg)
{
	size_t		index;
	char		*string;

	index = 0;
	string = itf_reg->vector->buffer;
	while (string[index] != '\0')
	{
		if (string[index] == '\\')
		{
			log_print(sh_reg, LOG_INFO, "Found an escape sequence.\n");

			log_print(sh_reg, LOG_INFO, "Quote is escaped!\n");
		}
		else if ()
		{
			log_print(sh_reg, LOG_INFO, "Found an escaped backslash.\n");
		}
		else if ()
		{
			log_print(sh_reg, LOG_INFO, "Newline is escaped!\n");
		}
		++index;
	}
}
