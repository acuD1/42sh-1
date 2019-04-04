/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_states.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 02:28:53 by cempassi          #+#    #+#             */
/*   Updated: 2019/04/04 05:50:21 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	expansion_machine(t_machine *machine)
{
	if (ft_strchr(EXP_INTERUPT, *machine->input) || !*machine->input)
	{
		machine->quote = machine->quote == QUOTE_INT ? QUOTE_ON : QUOTE_OFF;
		machine->last_machine = E_EXP;
		machine->state = OUT;
	}
	else
	{
		machine->last_machine = E_EXP;
		ft_strncat(machine->buffer, machine->input, 1);
		machine->input++;
	}
}
