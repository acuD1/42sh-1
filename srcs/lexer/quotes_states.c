/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_states.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 13:34:28 by cempassi          #+#    #+#             */
/*   Updated: 2019/04/03 19:44:29 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	backslash_machine(t_machine *machine)
{
	machine->last_machine = machine->state;
	fill_buffer_output(machine);
	if (*machine->input)
		machine->input++;
}

void	single_quote_machine(t_machine *machine)
{
	if (*machine->input == '\'')
	{
		machine->last_machine = machine->state;
		machine->state = OUT;
		machine->process = out_machine;
	}
	else
	{
		machine->last_machine = SQTE;
		ft_strncat(machine->buffer, machine->input, 1);
	}
	machine->input++;
}
