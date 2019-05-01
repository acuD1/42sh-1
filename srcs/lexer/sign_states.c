/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sign_states.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 18:56:27 by cempassi          #+#    #+#             */
/*   Updated: 2019/05/01 01:22:13 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	double_sign_machine(t_lexer *machine)
{
	int		checker;

	checker = 0;
	if (ft_strchr(DOUBLE_SIGN, *machine->input) != NULL)
	{
		if (*machine->buffer == '|' && *machine->input == '|' && ++checker)
			machine->last_lexer = E_OR;
		else if (*machine->buffer == ';' && *machine->input == ';' && ++checker)
			machine->last_lexer = E_DSEMI;
		else if (*machine->buffer == '&' && *machine->input == '&' && ++checker)
			machine->last_lexer = E_DAND;
		else if (*machine->buffer == '=' && *machine->input == '=' && ++checker)
			machine->last_lexer = E_DEQ;
		else if (*machine->buffer == '!' && *machine->input == '=' && ++checker)
			machine->last_lexer = E_NOTEQ;
		if (checker != FALSE)
			++machine->input;
	}
	if (*machine->buffer == '=' && *machine->input != '=')
		machine->state = L_STRING;
	else
		machine->state = L_OUT;
}

int		double_dispatcher(t_lexer *machine)
{
	int		checker;

	checker = 0;
	if (*machine->input == '>')
	{
		++checker;
		machine->state = L_GREATER;
	}
	else if (*machine->input == '<')
	{
		++checker;
		machine->state = L_LESSER;
	}
	else if (ft_strchr(DOUBLE_SIGN, *machine->input) != NULL)
	{
		++checker;
		machine->state = L_DSIGN;
	}
	return (checker);
}

void	and_machine(t_lexer *machine)
{
	if (ft_strchr("<>", *machine->input))
	{
		machine->last_lexer = *machine->input == '>' ? E_ANDGREAT : E_ANDLESS;
		machine->input++;
		if (machine->last_lexer == E_ANDGREAT && *machine->input == '>')
		{
			machine->last_lexer = E_ANDDGREAT;
			machine->input++;
		}
	}
	machine->state = L_OUT;
}

void	sign_machine(t_lexer *machine)
{
	if (*machine->input == '\'')
		machine->state = L_SQTE;
	else if (*machine->input == '\"')
		machine->state = L_DQTE;
	else if (*machine->input == '&')
		machine->state = L_AND;
	else if (double_dispatcher(machine) != FALSE)
		ft_strncat(machine->buffer, machine->input, 1);
	else
		fill_buffer_output(machine);
	++machine->input;
}
