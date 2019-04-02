/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_states.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 13:34:28 by cempassi          #+#    #+#             */
/*   Updated: 2019/04/02 15:51:10 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	backslash_machine(t_state *machine)
{
	machine->last_state = machine->state;
	fill_buffer_output(machine);
	if (*machine->input)
		machine->input++;
}

void	single_quote_machine(t_state *machine)
{
	if (*machine->input == '\'')
	{
		machine->last_state = machine->state;
		machine->state = OUT;
		machine->process = out_machine;
	}
	else
	{
		machine->last_state = SQTE;
		ft_strncat(machine->buffer, machine->input, 1);
	}
	machine->input++;
}
