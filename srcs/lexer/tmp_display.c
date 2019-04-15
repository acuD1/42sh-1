/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp_display.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 16:13:18 by cempassi          #+#    #+#             */
/*   Updated: 2019/04/15 18:17:34 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <stdio.h>
void		print_list(t_list *list)
{
	t_token *token;
	token = list->data;
	const static char *signs[14] = {"&&", "OR", ";;", "<<", ">>", "<&", ">&"
		, "<>", "<<-", ">|"};
	const static char *script[14] = {CASE, DO, DONE, ELIF, ELSE, ESAC, FI, FOR
		, IF, IN, THEN, UNTIL, WHILE};

	ft_putchar('\n');
	if (token->type < SINGLE_SIGNS || token->type == E_STRING )
	{
		ft_printf("type_id = [ %2d ] | type_name = [ %5.1c ] | data = [ %s ]\n",
				token->type,
				token->type < SINGLE_SIGNS ? ALLCHAR[token->type] : 'S'
				, token->data);
	}
	else if (token->type >= SINGLE_SIGNS && token->type < SIGNS)
	{
		ft_printf("type_id = [ %2d ] | type_name = [ %5s ] | data = [ %s ]\n",
				token->type, signs[token->type - SINGLE_SIGNS], token->data);

	}
	else if (token->type >= SIGNS && token->type < SIGNS + 13)
	{
		ft_printf("type_id = [ %2d ] | type_name = [ %5s ] | data = [ %s ]\n",
				token->type, script[token->type - SIGNS], token->data);
	}
	else
	{
		ft_printf("type_id = [ %2d ] | type_name = [ %5s ] | data = [ %s ]\n",
				token->type, "IO", token->data);
	}
}

void		del_token(void *token)
{
	t_token *tmp;

	tmp = token;
	ft_strdel(&tmp->data);
}