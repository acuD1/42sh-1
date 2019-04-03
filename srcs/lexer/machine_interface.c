/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   machine_interface.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 16:28:28 by ffoissey          #+#    #+#             */
/*   Updated: 2019/04/03 19:44:29 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	start_machine(t_machine *machine)
{
	if (!*machine->input)
		machine->process = end_machine;
	else if (*machine->input == ' ' || *machine->input == '\t')
	{
		machine->state = SPACE;
		machine->process = space_machine;
	}
	else if (ft_strchr(FINALCHAR, *machine->input) || *machine->input == '~')
	{
		machine->state = SIGN;
		machine->process = sign_machine;
	}
	else
	{
		machine->state = LETTER;
		machine->process = letter_machine;
	}
}

void	end_machine(t_machine *machine)
{
	if (*machine->buffer)
	{
		machine->state = OUT;
		machine->process = out_machine;
	}
	else
	{
		machine->state = END;
		machine->process = NULL;
	}
}

void	fill_buffer_output(t_machine *machine)
{
	ft_strncat(machine->buffer, machine->input, 1);
	machine->state = OUT;
	machine->process = out_machine;
}

void	out_machine(t_machine *machine)
{
	t_list	*node;
	t_token	token;

	token = generate_token(machine);
	if (!(node = ft_lstnew(&token, sizeof(token))))
		return ;
	ft_lstaddback(&machine->tokens, node);
	machine->state = START;
	machine->last_machine = START;
	machine->process = start_machine;
}
