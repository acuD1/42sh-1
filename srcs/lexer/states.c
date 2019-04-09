/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 17:03:31 by cempassi          #+#    #+#             */
/*   Updated: 2019/04/04 04:14:16 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	number_machine(t_machine *machine)
{
	if (machine->last_machine != E_IO_NUMBER && ft_isdigit(*machine->input))
	{
		machine->last_machine = E_IO_NUMBER;
		ft_strncat(machine->buffer, machine->input, 1);
		machine->input++;
	}
	else if (machine->last_machine == E_IO_NUMBER)
		machine->state = ft_strchr("<>", *machine->input) ? OUT : LETTER;
}

void	letter_machine(t_machine *machine)
{
	machine->last_machine = E_STRING;
	if (ft_strchr(FINALCHAR, *machine->input))
		machine->state = OUT;
	else if (*machine->input)
	{
		ft_strncat(machine->buffer, machine->input, 1);
		machine->input++;
	}
	else
		machine->state = START;
}

void	space_machine(t_machine *machine)
{
	fill_buffer_output(machine);
	while (*machine->input == ' ' || *machine->input == '\t')
		machine->input++;
}
