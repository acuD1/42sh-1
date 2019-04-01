/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   machine_interface.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 16:28:28 by ffoissey          #+#    #+#             */
/*   Updated: 2019/04/01 20:33:44 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	start_machine(t_state *machine)
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

void	end_machine(t_state *machine)
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

void	out_machine(t_state *machine)
{
	t_list	*node;
	t_token	token;

	token = generate_token(machine);
	if (!(node = ft_lstnew(&token, sizeof(token))))
		return ;
	ft_lstaddback(&machine->lst, node);
	machine->state = START;
	machine->last_state = START;
	machine->process = start_machine;
}
