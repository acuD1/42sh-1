/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_states.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 13:34:28 by cempassi          #+#    #+#             */
/*   Updated: 2019/04/02 13:53:23 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	quote_machine(t_state *machine)
{
	ft_printf("current char input : %c\n", *machine->input);
	ft_strncat(machine->buffer, machine->input, 1);
	machine->last_state = machine->state;
	machine->state = OUT;
	machine->process = out_machine;
	machine->input++;
}
