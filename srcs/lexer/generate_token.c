/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 20:19:38 by cempassi          #+#    #+#             */
/*   Updated: 2019/04/02 14:02:41 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int		check_char(t_state *machine)
{
	int i;
	char	*s;

	i = 0;
	s = ALLCHAR;
	while (i < 24)
	{
		if (*machine->buffer == *(s + i))
			return (i);
		++i;
	}
	return (0);
}

int		check_script(t_state *machine)
{
	int		index;
	const static char *script[14] = {CASE, DO, DONE, ELIF, ELSE, ESAC, FI, FOR
									, IF, IN, THEN, UNTIL, WHILE};

	index = 0;
	while (index < 14)
	{
		if (ft_strequ(machine->buffer, script[index]))
			return (index + OFFSET);
		++index;
	}
	return (0);
}

int		define_type(t_state *machine)
{
	int		result;

	if (machine->last_state == EXP)
		return (E_EXP);
	else if (machine->last_state == BSL)
		return (E_BACKSLASH);
	else if ((result = check_char(machine)))
		return (result);
	else if ((result = check_script(machine)))
		return (result);
	return (E_STRING);
}

t_token generate_token(t_state *machine)
{
	t_token 		token;
	int				i;

	i = 0;
	token.type = define_type(machine);
	token.data = NULL;
	while (i <= 3)
	{
		if (token.type == machine->duplicate[i++])
			token.data = ft_strdup(machine->buffer);
	}
	ft_bzero(machine->buffer, BUFFER);
	machine->last_state = START;
	return (token);
}
