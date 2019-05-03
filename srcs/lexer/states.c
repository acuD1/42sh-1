/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 17:03:31 by cempassi          #+#    #+#             */
/*   Updated: 2019/05/01 22:42:55 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"

void	number_machine(t_lexer *machine)
{
	if (ft_isdigit(*machine->input) == TRUE)
	{
		machine->last_lexer = E_IO_NUMBER;
		ft_strncat(machine->buffer, machine->input, 1);
		++machine->input;
	}
	else if (ft_strchr("<>", *machine->input) != NULL)
		machine->state = L_OUT;
	else
	{
		machine->last_lexer = E_STRING;
		machine->state = L_STRING;
	}
}

void	string_special(t_lexer *machine)
{
	machine->last_lexer = E_SPSTRING;
	if (*machine->input == '\"')
		machine->state = L_DQTE;
	else if (*machine->input == '\'')
		machine->state = L_SQTE;
}

void	string_machine(t_lexer *machine)
{
	if (*machine->input == '\0')
		machine->state = L_START;
	if (ft_strchr(LETTER_INTERUPT, *machine->input) != NULL)
	{
		machine->state = L_OUT;
		return ;
	}
	else if (*machine->input == '=' && machine->last_lexer == E_STRING)
	{
		machine->last_lexer = E_ASSIGN;
		machine->state = L_OUT;
		++machine->input;
		return ;
	}
	else if (ft_strchr(LETTER_SPECIAL, *machine->input) != NULL)
		string_special(machine);
	else if (machine->last_lexer != E_SPSTRING)
		machine->last_lexer = E_STRING;
	if (*machine->input != '\0')
	{
		ft_strncat(machine->buffer, machine->input, 1);
		++machine->input;
	}
}
