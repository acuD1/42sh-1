/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_states.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 14:23:05 by cempassi          #+#    #+#             */
/*   Updated: 2019/04/30 14:06:29 by cempassi         ###   ########.fr       */
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
			++machine->input;
			return ;
		}
	}
	else if (*machine->input == '>' || *machine->input == '&')
	{
		if (*machine->buffer == '<' && *machine->input == '&' && ++checker)
			machine->state = LESSAND;
		else if (*machine->buffer == '<' && *machine->input == '>' && ++checker)
			machine->last_lexer = E_LESSGREAT;
	}
	if (checker != FALSE)
		++machine->input;
	machine->state = machine->state == LESSAND ? LESSAND : OUT;
}

void	greater_machine(t_lexer *machine)
{
	int		checker;

	checker = 0;
	if (ft_strchr(">&|", *machine->input) != NULL)
	{
		if (*machine->buffer == '>' && *machine->input == '>' && ++checker)
			machine->last_lexer = E_DGREAT;
		else if (*machine->buffer == '>' && *machine->input == '&' && ++checker)
			machine->state = GREATAND;
		else if (*machine->buffer == '>' && *machine->input == '|' && ++checker)
			machine->last_lexer = E_CLOBBER;
	}
	if (checker != FALSE)
		++machine->input;
	machine->state = machine->state == GREATAND ? GREATAND : OUT;
}

void	greatand_machine(t_lexer *machine)
{
	machine->last_lexer = E_GREATAND;
	*machine->buffer = '\0';
	if (*machine->input == '-')
	{
		fill_buffer_output(machine);
		++machine->input;
	}
	else
		while (ft_isdigit(*machine->input))
		{
			fill_buffer_output(machine);
			++machine->input;
		}
	machine->state = OUT;
}

void	lessand_machine(t_lexer *machine)
{
	machine->last_lexer = E_LESSAND;
	*machine->buffer = '\0';
	if (*machine->input == '-')
	{
		fill_buffer_output(machine);
		++machine->input;
	}
	else
		while (ft_isdigit(*machine->input))
		{
			fill_buffer_output(machine);
			++machine->input;
		}
	machine->state = OUT;
}
