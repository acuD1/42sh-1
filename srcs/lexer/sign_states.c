/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sign_states.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 18:56:27 by cempassi          #+#    #+#             */
/*   Updated: 2019/04/03 19:44:29 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	and_machine(t_machine *machine)
{
	if (*machine->input == '&')
	{
		machine->last_machine = SAND;
		machine->input++;
	}
	machine->state = OUT;
	machine->process = out_machine;
}

void	sign_machine(t_machine *machine)
{
	if (*machine->input == '\\')
	{
		machine->state = BSL;
		machine->process = backslash_machine;
	}
	else if (*machine->input == '&')
	{
		machine->state = SAND;
		machine->process = and_machine;
	}
	else if (*machine->input == '\'')
	{
		machine->state = SQTE;
		machine->process = single_quote_machine;
	}
	else if (*machine->input == '$')
	{
		machine->state = EXP;
		machine->process = expansion_machine;
	}
	else
		fill_buffer_output(machine);
	machine->input++;
}
