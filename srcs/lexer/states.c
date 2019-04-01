/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 17:03:31 by cempassi          #+#    #+#             */
/*   Updated: 2019/04/01 20:27:43 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	letter_machine(t_state *machine)
{
	if (ft_strchr(FINALCHAR, *machine->input))
	{
		machine->state = OUT;
		machine->process = out_machine;
	}
	else if (*machine->input)
	{
		ft_strncat(machine->buffer, machine->input, 1);
		machine->input++;
	}
	else
	{
		machine->state = START;
		machine->process = start_machine;
	}
}

void	sign_machine(t_state *machine)
{
	if (*machine->input == '\\')
	{
		machine->state = BSL;
		machine->process = quote_machine;
	}
	else if (*machine->input == '$')
	{
		machine->state = EXP;
		machine->process = expansion_machine;
	}
	else
	{
		ft_strncat(machine->buffer, machine->input, 1);
		machine->state = OUT;
		machine->process = out_machine;
	}
	machine->input++;
}

void	space_machine(t_state *machine)
{
	ft_strncat(machine->buffer, machine->input, 1);
	while (*machine->input == ' ' || *machine->input == '\t')
		machine->input++;
	machine->state = OUT;
	machine->process = out_machine;
}

void	expansion_machine(t_state *machine)
{
	if ((machine->last_state != EXP && *machine->input == '$')
			|| (!ft_strchr(FINALCHAR, *machine->input) && *machine->input))
	{
		machine->last_state = machine->state;
		ft_strncat(machine->buffer, machine->input, 1);
		if (!ft_isalnum(*machine->input) && *machine->input != '~')
		{
			machine->state = OUT;
			machine->process = out_machine;
		}
		machine->input++;
	}
	else
	{
		machine->last_state = machine->state;
		machine->state = OUT;
		machine->process = out_machine;
	}
}

void	quote_machine(t_state *machine)
{
	if (*machine->input && *machine->input == '\\')
		machine->input++;
	ft_strncat(machine->buffer, machine->input, 1);
	machine->state = OUT;
	machine->process = out_machine;
	machine->input++;
}
