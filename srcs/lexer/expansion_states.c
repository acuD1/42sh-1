/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_states.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 02:28:53 by cempassi          #+#    #+#             */
/*   Updated: 2019/04/29 17:47:59 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	expansion_machine(t_lexer *machine)
{
	if (ft_strchr(EXP_INTERUPT, *machine->input) || *machine->input == '\0')
	{
		machine->last_lexer = machine->quote ? E_QEXP : E_EXP;
		if (machine->quote == QUOTE_INT)
			machine->quote = QUOTE_ON;
		if (machine->quote == QUOTE_SP_INT)
			machine->quote = QUOTE_SP;
		machine->state = OUT;
	}
	else
	{
		machine->last_lexer = E_EXP;
		ft_strncat(machine->buffer, machine->input, 1);
		machine->input++;
	}
}
