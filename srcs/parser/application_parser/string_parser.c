/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 21:17:49 by cempassi          #+#    #+#             */
/*   Updated: 2019/05/02 19:10:03 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	flush_string(t_parser *parse)
{
	int		index;
	t_token *token;

	parse->state = P_STRING_FLUSH;
	index = ft_stcksize(&parse->stack);
	parse->process.av = (char **)malloc(sizeof(char *) * (index + 1));
	if (parse->process.av == NULL)
		return ;
	parse->process.av[index] = NULL;
	while (--index >= 0)
	{
		token = ft_stckpop(&parse->stack);
		parse->process.av[index] = token->data;
		free(token);
	}
}

void	filename_state(t_parser *parse)
{
	ft_stckpush(&parse->stack, &parse->token, sizeof(t_token));
	get_token(parse);
	parse->state = P_FILENAME;
}

void	special_string_parser(t_parser *parse)
{
	parse->state = P_SPSTRING;
	parse->token.type = E_STRING;
	if ((parse->token.data = string_expansion(parse, parse->token.data)))
	{
		ft_stckpush(&parse->stack, &parse->token, sizeof(t_token));
		get_token(parse);
	}
}

void	string_parser(t_parser *parse)
{
	parse->state = P_STRING;
	ft_stckpush(&parse->stack, &parse->token, sizeof(t_token));
	get_token(parse);
}
