/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 14:23:19 by ffoissey          #+#    #+#             */
/*   Updated: 2019/05/01 17:01:41 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <stdlib.h>

static void		init_process(t_lexer *machine)
{
	machine->process[L_START] = start_lexer;
	machine->process[L_STRING] = string_machine;
	machine->process[L_IO_NUMBER] = number_machine;
	machine->process[L_SIGN] = sign_machine;
	machine->process[L_DSIGN] = double_sign_machine;
	machine->process[L_GREATER] = greater_machine;
	machine->process[L_LESSER] = lesser_machine;
	machine->process[L_GREATAND] = greatand_machine;
	machine->process[L_LESSAND] = lessand_machine;
	machine->process[L_SQTE] = single_quote_machine;
	machine->process[L_DQTE] = double_quote_machine;
	machine->process[L_AND] = and_machine;
	machine->process[L_OUT] = out_lexer;
	machine->process[L_END] = end_machine;
}

static void		init_special(t_lexer *machine)
{
	machine->special_signs[0] = E_DAND;
	machine->special_signs[1] = E_OR;
	machine->special_signs[2] = E_DSEMI;
	machine->special_signs[3] = E_DLESS;
	machine->special_signs[4] = E_DGREAT;
	machine->special_signs[5] = E_LESSAND;
	machine->special_signs[6] = E_GREATAND;
	machine->special_signs[7] = E_LESSGREAT;
	machine->special_signs[8] = E_DLESSDASH;
	machine->special_signs[9] = E_CLOBBER;
	machine->special_signs[10] = E_DEQ;
	machine->special_signs[11] = E_NOTEQ;
	machine->special_signs[12] = E_ANDDGREAT;
}

static void		init_lexer(t_lexer *machine)
{
	ft_bzero(machine, sizeof(t_lexer));
	machine->state = L_START;
	machine->last_lexer = E_DEFAULT;
	init_process(machine);
	init_special(machine);
	machine->duplicate[0] = E_STRING;
	machine->duplicate[1] = E_IO_NUMBER;
	machine->duplicate[2] = E_DB_QUOTE;
	machine->duplicate[3] = E_ASSIGN;
}

t_list			*lexer(char *input)
{
	t_lexer	machine;

	if (input == NULL)
		return (NULL);
	while (*input == '\t' || *input == ' ')
		input++;
	if (*input == '\0')
		return (NULL);
	init_lexer(&machine);
	machine.input = input;
	while (machine.state != L_FINISH)
		machine.process[machine.state](&machine);
	return (machine.tokens);
}
