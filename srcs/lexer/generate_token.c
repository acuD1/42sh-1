/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 20:19:38 by cempassi          #+#    #+#             */
/*   Updated: 2019/04/01 20:47:59 by cempassi         ###   ########.fr       */
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

	if ((result = check_char(machine)))
		return (result);
	if ((result = check_script(machine)))
		return (result);
	return (E_STRING);
}


t_token generate_token(t_state *machine)
{
	t_token 		token;
	enum e_type 	duplicate[3];
	int				i;

	i = 0;
	token.data = NULL;
	if (machine->last_state == EXP)
		token.type = E_EXP;
	else
		token.type = define_type(machine);
	while (i <= 2)
	{
		if (token.type == duplicate[i++])
			token.data = ft_strdup(machine->buffer);
	}
	ft_bzero(machine->buffer, BUFFER);
	machine->last_state = START;
	return (token);
}
