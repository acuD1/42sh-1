/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 20:19:38 by cempassi          #+#    #+#             */
/*   Updated: 2019/04/03 23:33:45 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int		check_last_machine(t_machine *machine)
{
	int		i;

	i = 0;
	while (i < TOKEN_WITH_DATA)
	{
		if (machine->last_machine == machine->duplicate[i])
			return (machine->duplicate[i]);
		i++;
	}
	i = 0;
	while (i < SPECIAL_SIGNS)
	{
		if (machine->last_machine == machine->special_signs[i])
			return (machine->special_signs[i]);
		i++;
	}
	if (machine->last_machine == E_IO_NUMBER)
		return (E_IO_NUMBER);
	return (0);
}

int		check_char(t_machine *machine)
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

int		check_script(t_machine *machine)
{
	int		index;
	const static char *script[14] = {CASE, DO, DONE, ELIF, ELSE, ESAC, FI, FOR
									, IF, IN, THEN, UNTIL, WHILE};

	index = 0;
	while (index < 14)
	{
		if (ft_strequ(machine->buffer, script[index]))
			return (index + SIGNS);
		++index;
	}
	return (0);
}

int		define_type(t_machine *machine)
{
	int		result;

	if ((result = check_last_machine(machine)))
		return (result);
	else if ((result = check_char(machine)))
		return (result);
	else if ((result = check_script(machine)))
		return (result);
	return (E_STRING);
}

t_token generate_token(t_machine *machine)
{
	t_token 		token;
	int				i;

	i = 0;
	token.type = define_type(machine);
	token.data = NULL;
	while (i < TOKEN_WITH_DATA)
	{
		if (token.type == machine->duplicate[i++])
			token.data = ft_strdup(machine->buffer);
	}
	ft_bzero(machine->buffer, BUFFER);
	machine->last_machine = E_DEFAULT;
	return (token);
}
