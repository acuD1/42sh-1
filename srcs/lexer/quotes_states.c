/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_states.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 13:34:28 by cempassi          #+#    #+#             */
/*   Updated: 2019/04/04 05:51:30 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	backslash_machine(t_machine *machine)
{
	if (*machine->input == 'n')
	{
		machine->last_machine = E_NEWLINE;
		machine->state = OUT;
	}
	else
	{
		machine->last_machine = E_BACKSLASH;
		fill_buffer_output(machine);
	}
	if (*machine->input)
		machine->input++;
}

void	single_quote_machine(t_machine *machine)
{
	if (*machine->input == '\'')
	{
		machine->last_machine = E_QUOTE;
		machine->state = OUT;
	}
	else
	{
		machine->last_machine = E_QUOTE;
		ft_strncat(machine->buffer, machine->input, 1);
	}
	machine->input++;
}

void	quote_dispatcher(t_machine *machine)
{
	if (*machine->input == '\\')
		machine->state = BSL;
	else if (*machine->input == '\'')
		machine->state = SQTE;
	else if (*machine->input == '`')
		machine->state = BQTE;
	else if (*machine->input == '$')
		machine->state = EXP;
	machine->input++;
}

void	double_quote_machine(t_machine *machine)
{
	if (machine->quote && *machine->input == '\"')
	{
		machine->last_machine = E_DB_QUOTE;
		machine->state = OUT;
		machine->quote = QUOTE_OFF;
		return ;
	}
	if (machine->quote == QUOTE_INT)
		quote_dispatcher(machine);
	else if (ft_strchr(QUOTE_INTERUPT, *machine->input))
	{
		machine->quote = QUOTE_INT;
		machine->last_machine = E_DB_QUOTE;
		machine->state = OUT;
		return ;
	}
	else if (*machine->input)
	{
		ft_strncat(machine->buffer, machine->input, 1);
		machine->quote = QUOTE_ON;
		machine->input++;
	}
	else
		machine->state = START;
}
