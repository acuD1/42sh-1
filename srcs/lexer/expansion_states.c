/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_states.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 02:28:53 by cempassi          #+#    #+#             */
/*   Updated: 2019/04/24 03:17:00 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	expansion_machine(t_lexer *machine)
{
	if (ft_strchr(EXP_INTERUPT, *machine->input) != NULL
			|| *machine->input == NULL)
	{
		if (machine->quote == QUOTE_INT)
			machine->quote = QUOTE_OFF;
		if (machine->quote == QUOTE_SP_INT)
			machine->quote = QUOTE_SP;
		machine->last_lexer = E_EXP;
		machine->state = OUT;
	}
	else
	{
		machine->last_lexer = E_EXP;
		ft_strncat(machine->buffer, machine->input, 1);
		machine->input++;
	}
}
