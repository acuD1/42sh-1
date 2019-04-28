/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 17:03:31 by cempassi          #+#    #+#             */
/*   Updated: 2019/04/24 02:33:45 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	number_machine(t_lexer *machine)
{
	if (machine->last_lexer != E_IO_NUMBER
			&& ft_isdigit(*machine->input) == TRUE)
	{
		machine->last_lexer = E_IO_NUMBER;
		ft_strncat(machine->buffer, machine->input, 1);
		++machine->input;
	}
	else if (machine->last_lexer == E_IO_NUMBER && *machine->input != '\0')
		machine->state = ft_strchr("<>", *machine->input) != NULL
							? OUT : LETTER;
	else
	{
		machine->last_lexer = E_STRING;
		machine->state = LETTER;
	}
}

void	letter_machine(t_lexer *machine)
{
	if (ft_strchr(LETTER_INTERUPT, *machine->input) != NULL)
		machine->state = OUT;
	else if (*machine->input == '=' && machine->last_lexer == E_STRING)
	{
		machine->last_lexer = E_ASSIGN;
		machine->state = OUT;
		++machine->input;
	}
	else if (ft_strchr(LETTER_TO_QUOTE, *machine->input) != NULL)
	{
		machine->state = *machine->input == '\'' ? SQTE : DQTE;
		if (machine->state == DQTE)
			machine->quote = QUOTE_SP;
		if (*machine->input != '$')
			++machine->input;
	}
	else if (*machine->input != '\0')
	{
		machine->last_lexer = E_STRING;
		ft_strncat(machine->buffer, machine->input, 1);
		++machine->input;
	}
	else
		machine->state = START;
}
