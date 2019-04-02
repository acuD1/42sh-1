/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 14:23:19 by ffoissey          #+#    #+#             */
/*   Updated: 2019/04/02 13:51:11 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static void	state_handler(t_state *machine)
{
	if (machine->state == END)
		return ;
	machine->process(machine);
	return (state_handler(machine));
}

void		init_machine(t_state *machine)
{
	ft_bzero(machine, sizeof(t_state));
	machine->process = start_machine;
	machine->state = START;
	machine->duplicate[0] = E_EXP;
	machine->duplicate[1] = E_BACKSLASH;
	machine->duplicate[2] = E_STRING;
	machine->duplicate[3] = E_BACKSLASH;

}

t_list		*lexer(char *input)
{
	t_state	machine;

	if (!input || !*input)
		return (NULL);
	while (*input == '\t' || *input == ' ')
		input++;
	init_machine(&machine);
	machine.input = input;
	state_handler(&machine);
	return (machine.lst);
}


/////////////////////////////////////////////////////////

void		print_list(t_list *list)
{
	t_token *token;
	token = list->data;
	const static char *script[14] = {CASE, DO, DONE, ELIF, ELSE, ESAC, FI, FOR
									, IF, IN, THEN, UNTIL, WHILE};

	if (token->type < 24 || token->type == E_STRING )
	{
	ft_printf("type_id = [ %2d ] | type_name = [ %5.1c ] | data = [ %s ]\n",
			token->type,
			token->type < 25 ? ALLCHAR[token->type] : 'S'
			, token->data);
	}
	else
	{
		ft_printf("type_id = [ %2d ] | type_name = [ %5s ] | data = [ %s ]\n",
				token->type, script[token->type - 24], token->data);
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
