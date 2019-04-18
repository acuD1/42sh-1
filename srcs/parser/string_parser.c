/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 21:17:49 by cempassi          #+#    #+#             */
/*   Updated: 2019/04/19 01:43:07 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	flush_string(t_parser *parse)
{
	int		index;
	t_token *token;

	parse->state = P_STRING_FLUSH;
	index = ft_stcksize(&parse->stack);
	parse->command.av = (char **)malloc(sizeof(char *) * (index + 1));
	parse->command.av[index] = NULL;
	while (--index >= 0)
	{
		token = ft_stckpop(&parse->stack);
		parse->command.av[index] = token->data;
		free(token);
	}
}

void	string_parser(t_parser *parse)
{
	parse->state = P_STRING;
	ft_stckpush(&parse->stack, &parse->token, sizeof(t_token));
	get_token(parse);
}
