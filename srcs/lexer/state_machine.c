/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_machine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 16:28:28 by ffoissey          #+#    #+#             */
/*   Updated: 2019/03/26 23:02:40 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	start_machine(t_state *machine)
{
	char *tmp;

	if (!*machine->input)
		machine->process = end_machine;
	else if (machine->quote)
	{
		tmp = ft_strchr(machine->input, '\'');
		ft_strncat(machine->buffer, machine->input, tmp - machine->input);
		machine->input = tmp;
		machine->state = OUT;
		machine->process = out_machine;
		machine->quote = 0;
	}
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
	if (*machine->input == '\'')
	{
		machine->quote = 1;
		ft_strncat(machine->buffer, machine->input, 1);
		machine->state = OUT;
		machine->process = out_machine;
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

void	expansion_machine(t_state *machine)
{
	if ((machine->last_state != EXP && *machine->input == '$')
			|| !ft_strchr(FINALCHAR, *machine->input))
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

void	space_machine(t_state *machine)
{
	ft_strncat(machine->buffer, machine->input, 1);
	while (*machine->input == ' ' || *machine->input == '\t')
		machine->input++;
	machine->state = OUT;
	machine->process = out_machine;
}
