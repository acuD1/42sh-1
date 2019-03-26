/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 14:23:19 by ffoissey          #+#    #+#             */
/*   Updated: 2019/03/26 22:35:31 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int		define_type(t_state *machine)
{
	int		i;
	int		j;
	char	*s;
	const static char *script[14] = {CASE, DO, DONE, ELIF, ELSE, ESAC, FI, FOR
									, IF, IN, THEN, UNTIL, WHILE};

	s = ALLCHAR;
	i = -1;
	while (++i < 24)
		if (*machine->buffer == *(s + i))
			break ;
	j = -1;
	while (++j < 14 && i == 24)
		if (ft_strequ(machine->buffer, script[j]))
			break ;
	return (i + j);
}

t_token generate_token(t_state *machine)
{
	t_token token;
	int		i;

	i = define_type(machine);
	token.data = NULL;
	token.type = machine->last_state == EXP ? E_EXP : i;
	if (token.type == E_EXP || token.type == 38)
		token.data = ft_strdup(machine->buffer);
	ft_bzero(machine->buffer, BUFFER);
	machine->last_state = START;
	return (token);
}

static void	state_handler(t_state *machine)
{
	if (machine->state == END)
		return ;
	machine->process(machine);
	return (state_handler(machine));
}

t_list		*lexer(char *input)
{
	t_state	machine;

	if (!input || !*input)
		return (NULL);
	while (*input == '\t' || *input == ' ')
		input++;
	ft_bzero(&machine, sizeof(machine));
	machine.input = input;
	machine.process = start_machine;
	machine.state = START;
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

	if (token->type < 24 || token->type == 38 )
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

	if (ac > 1)
	{
		lst = lexer(av[1]);
		ft_lstiter(lst, print_list);
	}
	return (0);
}
