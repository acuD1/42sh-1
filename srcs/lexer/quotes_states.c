/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_states.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 13:34:28 by cempassi          #+#    #+#             */
/*   Updated: 2019/04/03 22:48:34 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	backslash_machine(t_machine *machine)
{
	machine->last_machine = E_BACKSLASH;
	fill_buffer_output(machine);
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
