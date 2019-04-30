/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_parser.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 20:43:54 by cempassi          #+#    #+#             */
/*   Updated: 2019/04/30 22:06:43 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#include "parser.h"


void	expansion_parser(t_parser *parse)
{
	t_list	*node;
	char	*data;

	parse->state = P_EXP;
	parse->token.type = E_STRING;
	data = NULL;
	if ((node = ft_lstfind(parse->env, parse->token.data, find_variable)))
		data = ((t_variable *)node->data)->data;
	else
		data = ft_strdup("");
	ft_strdel(&parse->token.data);
	parse->token.data = ft_strdup(data);
	ft_stckpush(&parse->stack, &parse->token, sizeof(t_token));
	get_token(parse);
}
