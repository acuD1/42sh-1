/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   machine_interface.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 16:28:28 by ffoissey          #+#    #+#             */
/*   Updated: 2019/04/24 03:00:49 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	start_lexer(t_lexer *machine)
{
	if (machine->quote != QUOTE_OFF)
		machine->state = DQTE;
	else if (*machine->input == '\0')
		machine->state = END;
	else if (*machine->input == ' ' || *machine->input == '\t')
	{
		while (*machine->input == ' ' || *machine->input == '\t')
			++machine->input;
	}
	else if (ft_strchr(SIGN_DETECT, *machine->input) != NULL)
		machine->state = SIGN;
	else if (ft_isdigit(*machine->input) == TRUE)
		machine->state = IO_NUMBER;
	else
		machine->state = LETTER;
}

void	end_machine(t_lexer *machine)
{
	if (*machine->buffer != '\0')
		machine->state = OUT;
	else if (machine->last_lexer != E_END)
	{
		machine->last_lexer = E_END;
		machine->state = OUT;
	}
	else
		machine->state = FINISH;
}

void	fill_buffer_output(t_lexer *machine)
{
	ft_strncat(machine->buffer, machine->input, 1);
	machine->state = OUT;
}

void	out_lexer(t_lexer *machine)
{
	t_list	*node;
	t_token	token;

	token = generate_token(machine);
	if ((node = ft_lstnew(&token, sizeof(token))) == NULL)
		return ;
	ft_lstaddback(&machine->tokens, node);
	machine->state = START;
}
