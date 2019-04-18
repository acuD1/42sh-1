/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 20:19:38 by cempassi          #+#    #+#             */
/*   Updated: 2019/04/18 15:15:23 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int		check_script(t_lexer *machine)
{
	int					index;
	const static char	*script[14] = {CASE, DO, DONE, ELIF, ELSE, ESAC, FI, FOR
									, IF, IN, THEN, UNTIL, WHILE};

	index = 0;
	while (index < 14)
	{
		if (ft_strequ(machine->buffer, script[index]))
			return (index + SIGNS);
		++index;
	}
	return (E_STRING);
}

int		check_last_lexer(t_lexer *machine)
{
	int		i;

	i = 0;
	if (machine->last_lexer == E_STRING)
		return (check_script(machine));
	while (i < TOKEN_WITH_DATA)
	{
		if (machine->last_lexer == machine->duplicate[i])
			return (machine->duplicate[i]);
		i++;
	}
	i = 0;
	while (i < SPECIAL_SIGNS)
	{
		if (machine->last_lexer == machine->special_signs[i])
			return (machine->special_signs[i]);
		i++;
	}
	if (machine->last_lexer == E_IO_NUMBER)
		return (E_IO_NUMBER);
	if (machine->last_lexer == E_NEWLINE)
		return (E_NEWLINE);
	return (-1);
}

int		check_char(t_lexer *machine)
{
	int		i;
	char	*s;

	i = 0;
	s = ALLCHAR;
	while (i < SINGLE_SIGNS)
	{
		if (*machine->buffer == *(s + i))
			return (i);
		++i;
	}
	return (0);
}

int		define_type(t_lexer *machine)
{
	int		result;

	if ((result = check_last_lexer(machine)) >= 0)
		return (result);
	else if ((result = check_char(machine)))
		return (result);
	else if (machine->last_lexer == E_DB_QUOTE || machine->quote == QUOTE_ON)
		return (E_DB_QUOTE);
	return (E_STRING);
}

t_token	generate_token(t_lexer *machine)
{
	t_token		token;
	int			i;

	i = 0;
	token.type = define_type(machine);
	token.data = NULL;
	while (i < TOKEN_WITH_DATA)
	{
		if (token.type == machine->duplicate[i++] && *machine->buffer)
			token.data = ft_strdup(machine->buffer);
	}
	ft_bzero(machine->buffer, BUFFER);
	machine->last_lexer = E_DEFAULT;
	return (token);
}
