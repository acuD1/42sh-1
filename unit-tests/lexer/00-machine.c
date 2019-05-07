/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00-machine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 16:39:20 by cempassi          #+#    #+#             */
/*   Updated: 2019/05/07 15:03:04 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

int				lexer_cmp(void *data1, void *data2)
{
	t_token		*L;
	t_token		*R;

	L = data1;
	R = data2;
	if (L->type != R->type)
		return (-1);
	if (L->data && R->data)
		return (ft_strequ(L->data, R->data) ? 0 : -1);
	return (0);
}

int				test_null_pointer(void)
{
	if (lexer(NULL) == NULL)
		return (ISTRUE);
	else
		return (ISFALSE);
}

int				test_simple_string(void)
{
	t_list		*tok_ref;
	t_list		*tok_lst;
	t_list		*node;
	t_token		token;

	tok_ref = NULL;
	token.type = E_STRING;
	token.data = "echo";
	node = ft_lstnew(&token, sizeof(t_token));
	ft_lstaddback(&tok_ref, node);
	tok_lst = lexer("echo");
	if (ft_lstcmp(tok_ref, tok_lst, lexer_cmp))
		return (ISFALSE);
	ft_lstdel(&tok_lst, del_token);
	return (ISTRUE);
}

t_result		basic_lexer_test(int print_on)
{
	t_stack		tests;

	ft_stckinit(&tests);
	load_test(&tests, "Simple Sting", test_simple_string);
	load_test(&tests, "Null string protection", test_null_pointer);
	return(run_test(&tests, "Lexer basic tests", print_on));
}
