/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sign_states.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 18:56:27 by cempassi          #+#    #+#             */
/*   Updated: 2019/04/24 02:36:05 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	double_sign_machine(t_lexer *machine)
{
	int		checker;

	checker = 0;
	if (ft_strchr(DOUBLE_SIGN, *machine->input))
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
		if (checker)
			machine->input++;
	}
	if (*machine->buffer == '=' && *machine->input != '=')
		machine->state = LETTER;
	else
		machine->state = OUT;
}

void	tilde_machine(t_lexer *machine)
{
	machine->last_lexer = E_TILDE;
	if(ft_strchr(TILDE_INTERUPT, *machine->input) || !*machine->input)
	{
		if (*machine->input && *machine->input != ' ')
			machine->quote = QUOTE_SP;
		machine->state = OUT;
	}
	else
	{
		ft_strncat(machine->buffer, machine->input, 1);
		machine->input++;
	}
}

int		double_dispatcher(t_lexer *machine)
{
	int		checker;

	checker = 0;
	if (*machine->input == '>')
	{
		checker++;
		machine->state = GREATER;
	}
	else if (*machine->input == '<')
	{
		checker++;
		machine->state = LESSER;
	}
	else if (ft_strchr(DOUBLE_SIGN, *machine->input))
	{
		checker++;
		machine->state = DSIGN;
	}
	return (checker);
}

void	sign_machine(t_lexer *machine)
{
	if (*machine->input == '\\')
		machine->state = BSL;
	else if (*machine->input == '\'')
		machine->state = SQTE;
	else if (*machine->input == '\"')
		machine->state = DQTE;
	else if (*machine->input == '$')
		machine->state = EXP;
	else if (*machine->input == '~')
		machine->state = TILDE;
	else if (double_dispatcher(machine))
		ft_strncat(machine->buffer, machine->input, 1);
	else
		fill_buffer_output(machine);
	machine->input++;
}
