/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 14:23:19 by ffoissey          #+#    #+#             */
/*   Updated: 2019/04/18 19:35:21 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <stdlib.h>

static void		init_process(t_lexer *machine)
{
	machine->process[START] = start_lexer;
	machine->process[LETTER] = letter_machine;
	machine->process[IO_NUMBER] = number_machine;
	machine->process[SIGN] = sign_machine;
	machine->process[DSIGN] = double_sign_machine;
	machine->process[GREATER] = greater_machine;
	machine->process[LESSER] = lesser_machine;
	machine->process[EXP] = expansion_machine;
	machine->process[BSL] = backslash_machine;
	machine->process[SQTE] = single_quote_machine;
	machine->process[DQTE] = double_quote_machine;
	machine->process[OUT] = out_lexer;
	machine->process[END] = end_machine;
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
}

static void		init_lexer(t_lexer *machine)
{
	ft_bzero(machine, sizeof(t_lexer));
	machine->state = START;
	machine->last_lexer = E_DEFAULT;
	init_process(machine);
	init_special(machine);
	machine->duplicate[0] = E_EXP;
	machine->duplicate[1] = E_STRING;
	machine->duplicate[2] = E_BACKSLASH;
	machine->duplicate[3] = E_IO_NUMBER;
	machine->duplicate[4] = E_QUOTE;
	machine->duplicate[5] = E_DB_QUOTE;
	machine->duplicate[6] = E_ASSIGN;
}

t_list			*lexer(char *input)
{
	t_lexer	machine;

	if (!input || !*input)
		return (NULL);
	while (*input == '\t' || *input == ' ')
		input++;
	init_lexer(&machine);
	machine.input = input;
	while (machine.state != FINISH)
		machine.process[machine.state](&machine);
	return (machine.tokens);
}
