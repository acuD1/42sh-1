/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_states.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 14:23:05 by cempassi          #+#    #+#             */
/*   Updated: 2019/04/23 14:36:30 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	greatand_machine(t_lexer *machine)
{
	machine->last_lexer = E_GREATAND;
	if (ft_isdigit(*machine->input) || *machine->input == '-')
	{
		*machine->buffer = '\0';
		fill_buffer_output(machine);
		machine->input++;
	}
	machine->state = OUT;

}
