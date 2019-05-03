/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_states.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 13:34:28 by cempassi          #+#    #+#             */
/*   Updated: 2019/05/03 15:27:09 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	single_quote_machine(t_lexer *machine)
{
	if (*machine->input == '\0')
	{
		machine->state = L_OUT;
		return ;
	}
	if (*machine->input == '\'')
		machine->state = L_STRING;
	if (*machine->input != '\0')
	{
		ft_strncat(machine->buffer, machine->input, 1);
		++machine->input;
	}
	else
		machine->state = L_START;
}

void	double_quote_machine(t_lexer *machine)
{
	if (*machine->input == '\0')
	{
		machine->state = L_OUT;
		return ;
	}
	if (*machine->input == '\"')
		machine->state = L_STRING;
	if (*machine->input != '\0')
	{
		ft_strncat(machine->buffer, machine->input, 1);
		++machine->input;
	}
	else
		machine->state = L_START;
}
