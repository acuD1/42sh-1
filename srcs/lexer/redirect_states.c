/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_states.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 14:23:05 by cempassi          #+#    #+#             */
/*   Updated: 2019/04/24 01:52:54 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	lesser_machine(t_lexer *machine)
{
	int		checker;

	checker = 0;
	if (machine->last_lexer == E_DLESS && *machine->input == '-' && ++checker)
		machine->last_lexer = E_DLESSDASH;
	else if (*machine->buffer == '<' && *machine->input == '<')
	{
		if (machine->last_lexer != E_DLESS)
		{
			machine->last_lexer = E_DLESS;
			ft_strncat(machine->buffer, machine->input, 1);
			machine->input++;
			return ;
		}
	}
	else if (*machine->input == '>' || *machine->input == '&')
	{
		if (*machine->buffer == '<' && *machine->input == '&' && ++checker)
			machine->last_lexer = E_LESSAND;
		else if (*machine->buffer == '<' && *machine->input == '>' && ++checker)
			machine->last_lexer = E_LESSGREAT;
	}
	if (checker)
		machine->input++;
	machine->state = OUT;
}

void	greater_machine(t_lexer *machine)
{
	int		checker;

	checker = 0;
	if (ft_strchr(">&|", *machine->input))
	{
		if (*machine->buffer == '>' && *machine->input == '>' && ++checker)
			machine->last_lexer = E_DGREAT;
		else if (*machine->buffer == '>' && *machine->input == '&' && ++checker)
			machine->state = GREATAND;
		else if (*machine->buffer == '>' && *machine->input == '|' && ++checker)
			machine->last_lexer = E_CLOBBER;
	}
	if (checker)
		machine->input++;
	if (machine->state != GREATAND)
		machine->state = OUT;
}

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
