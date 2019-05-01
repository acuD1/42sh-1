/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_states.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 14:23:05 by cempassi          #+#    #+#             */
/*   Updated: 2019/05/01 17:07:04 by cempassi         ###   ########.fr       */
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
			machine->state = L_LESSAND;
		else if (*machine->buffer == '<' && *machine->input == '>' && ++checker)
			machine->last_lexer = E_LESSGREAT;
	}
	if (checker != FALSE)
		++machine->input;
	machine->state = machine->state == L_LESSAND ? L_LESSAND : L_OUT;
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
			machine->state = L_GREATAND;
		else if (*machine->buffer == '>' && *machine->input == '|' && ++checker)
			machine->last_lexer = E_CLOBBER;
	}
	if (checker != FALSE)
		++machine->input;
	machine->state = machine->state == L_GREATAND ? L_GREATAND : L_OUT;
}

void	greatand_machine(t_lexer *machine)
{
	machine->last_lexer = E_GREATAND;
	*machine->buffer = '\0';
	if (machine->io_detect == 1)
		machine->io_detect = 2;
	machine->state = L_OUT;
}

void	lessand_machine(t_lexer *machine)
{
	machine->last_lexer = E_LESSAND;
	*machine->buffer = '\0';
	if (machine->io_detect == 1)
		machine->io_detect = 2;
	machine->state = L_OUT;
}
