/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_states.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 13:34:28 by cempassi          #+#    #+#             */
/*   Updated: 2019/04/18 15:23:26 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	backslash_machine(t_lexer *machine)
{
	if (*machine->input == 'n')
	{
		machine->last_lexer = E_NEWLINE;
		machine->state = OUT;
	}
	else
	{
		machine->last_lexer = E_BACKSLASH;
		fill_buffer_output(machine);
	}
	if (*machine->input)
		machine->input++;
}

void	single_quote_machine(t_lexer *machine)
{
	if (*machine->input == '\'')
	{
		if (machine->input[1] == '\0' || machine->input[1] == ' ')
		{
			machine->last_lexer = E_QUOTE;
			machine->state = OUT;
		}
		else if (machine->input[1] == '\"')
			machine->state = DQTE;
		else
			machine->state = LETTER;
	}
	else
	{
		machine->last_lexer = E_QUOTE;
		ft_strncat(machine->buffer, machine->input, 1);
	}
	machine->input++;
}

void	quote_dispatcher(t_lexer *machine)
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

void	close_double_quote(t_lexer *machine)
{
	machine->last_lexer = E_DB_QUOTE;
	machine->state = OUT;
	machine->quote = QUOTE_OFF;
	machine->input++;
	return ;
}

void	double_quote_machine(t_lexer *machine)
{
	if (machine->quote && *machine->input == '\"')
		close_double_quote(machine);
	else if (machine->quote == QUOTE_INT)
		quote_dispatcher(machine);
	else if (ft_strchr(QUOTE_INTERUPT, *machine->input))
	{
		machine->quote = QUOTE_INT;
		machine->last_lexer = E_DB_QUOTE;
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
