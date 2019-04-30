/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp_display.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 16:13:18 by cempassi          #+#    #+#             */
/*   Updated: 2019/05/01 00:54:29 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <stdio.h>

void		print_token(t_list *list)
{
	t_token *token;
	token = list->data;
	static const char *signs[14] = {"&&", "OR", ";;", "<<", ">>", "<&", ">&"
		, "<>", "<<-", ">|", "==", "!="};
	static const char *script[14] = {CASE, DO, DONE, ELIF, ELSE, ESAC, FI, FOR
		, IF, IN, THEN, UNTIL, WHILE};

	if (token->type == E_STRING)
	{
		ft_printf("type_id = [ %2d ] | type_name = [ %5s ] | data = [ %s ]\n",
				token->type, "STRING", token->data);
	}
	else if (token->type == E_SPSTRING)
	{
		ft_printf("type_id = [ %2d ] | type_name = [ %5s ] | data = [ %s ]\n",
				token->type, "SPSTRING", token->data);
	}
	else if (token->type < SINGLE_SIGNS)
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
	else if (token->type == E_IO_NUMBER)
	{
		ft_printf("type_id = [ %2d ] | type_name = [ %5s ] | data = [ %s ]\n",
				token->type, "IO", token->data);
	}
	else if (token->type == E_ASSIGN)
	{
		ft_printf("type_id = [ %2d ] | type_name = [ %5s ] | data = [ %s ]\n",
				token->type, "ASSIGN", token->data);
	}
	else if (token->type == E_END)
	{
		ft_printf("type_id = [ %2d ] | type_name = [ %5s ] | data = [ %s ]\n",
				token->type, "END", token->data);
	}
}

void		del_token(void *token)
{
	t_token *tmp;

	tmp = token;
	ft_strdel(&tmp->data);
}
