/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 17:03:31 by cempassi          #+#    #+#             */
/*   Updated: 2019/04/18 16:00:26 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	number_machine(t_lexer *machine)
{
	if (machine->last_lexer != E_IO_NUMBER && ft_isdigit(*machine->input))
	{
		machine->last_lexer = E_IO_NUMBER;
		ft_strncat(machine->buffer, machine->input, 1);
		machine->input++;
	}
	else if (machine->last_lexer == E_IO_NUMBER)
		machine->state = ft_strchr("<>", *machine->input) ? OUT : LETTER;
}

void	letter_machine(t_lexer *machine)
{
	if (*machine->input == '=' && machine->last_lexer == E_STRING)
	{
		machine->last_lexer = E_ASSIGN;
		machine->state = OUT;
		machine->input++;
	}
	else if (ft_strchr(LETTER_TO_QUOTE, *machine->input))
	{
		machine->state = *machine->input == '\'' ? SQTE : DQTE;
		machine->input++;
	}
	else if (ft_strchr(LETTER_INTERUPT, *machine->input))
		machine->state = OUT;
	else if (*machine->input)
	{
		machine->last_lexer = E_STRING;
		ft_strncat(machine->buffer, machine->input, 1);
		machine->input++;
	}
	else
		machine->state = START;
}
