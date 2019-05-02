/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_states.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 13:34:28 by cempassi          #+#    #+#             */
/*   Updated: 2019/05/02 00:41:43 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	single_quote_machine(t_lexer *machine)
{
	if (*machine->input == '\'')
		machine->state = L_STRING;
	ft_strncat(machine->buffer, machine->input, 1);
	++machine->input;
}

void	double_quote_machine(t_lexer *machine)
{
	if (*machine->input == '\"')
		machine->state = L_STRING;
	ft_strncat(machine->buffer, machine->input, 1);
	++machine->input;
}
