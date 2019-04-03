/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 14:23:19 by ffoissey          #+#    #+#             */
/*   Updated: 2019/04/03 20:04:56 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static void	state_handler(t_machine *machine)
{
	if (machine->state == END)
		return ;
	machine->process(machine);
	return (state_handler(machine));
}

void		intit_states(t_machine *machine)
{
	machine->states[START].state = START;
	machine->states[START].process = start_machine;
	machine->states[LETTER].state = LETTER;
	machine->states[LETTER].process = letter_machine;
	machine->states[SAND].state = SAND;
	machine->states[SAND].process = and_machine;
	machine->states[SIGN].state = SIGN;
	machine->states[SIGN].process = sign_machine;
	machine->states[SPACE].state = SPACE;
	machine->states[SPACE].process = space_machine;
	machine->states[EXP].state = EXP;
	machine->states[EXP].process = expansion_machine;
	machine->states[BSL].state = BSL;
	machine->states[BSL].process = backslash_machine;
	machine->states[SQTE].state = SQTE;
	machine->states[SQTE].process = single_quote_machine;
	machine->states[OUT].state = OUT;
	machine->states[OUT].process = out_machine;
	machine->states[END].state = END;
	machine->states[END].process = end_machine;
}
void		init_machine(t_machine *machine)
{
	ft_bzero(machine, sizeof(t_machine));
	machine->current_state = machine->states[START];
	machine->process = start_machine;
	machine->state = START;
	machine->duplicate[0] = E_EXP;
	machine->duplicate[1] = E_BACKSLASH;
	machine->duplicate[2] = E_STRING;
	machine->duplicate[3] = E_BACKSLASH;
	machine->duplicate[4] = E_QUOTE;
}

t_list		*lexer(char *input)
{
	t_machine	machine;

	if (!input || !*input)
		return (NULL);
	while (*input == '\t' || *input == ' ')
		input++;
	init_machine(&machine);
	machine.input = input;
	state_handler(&machine);
	return (machine.tokens);
}


/////////////////////////////////////////////////////////

void		print_list(t_list *list)
{
	t_token *token;
	token = list->data;
	const static char *signs[14] = {DAND,};
	const static char *script[14] = {CASE, DO, DONE, ELIF, ELSE, ESAC, FI, FOR
									, IF, IN, THEN, UNTIL, WHILE};

	if (token->type < SINGLE_SIGNS || token->type == E_STRING )
	{
	ft_printf("type_id = [ %2d ] | type_name = [ %5.1c ] | data = [ %s ]\n",
			token->type,
			token->type < 25 ? ALLCHAR[token->type] : 'S'
			, token->data);
	}
	else if (token->type >= SINGLE_SIGNS && token->type < SIGNS)
	{
		ft_printf("type_id = [ %2d ] | type_name = [ %5s ] | data = [ %s ]\n",
				token->type, signs[token->type - SINGLE_SIGNS], token->data);

	}
	else
	{
		ft_printf("type_id = [ %2d ] | type_name = [ %5s ] | data = [ %s ]\n",
				token->type, script[token->type - SIGNS], token->data);
	}
}

void	del_list(t_list *list)
{
	t_token *tmp;

	tmp = list->data;
	ft_strdel(&tmp->data);
}

int		main(int ac, char **av)
{
	t_list *lst;

	ft_printf("E_STRING = %d\n", E_STRING);
	if (ac > 1)
	{
		lst = lexer(av[1]);
		ft_lstiter(lst, print_list);
	}
	return (0);
}
