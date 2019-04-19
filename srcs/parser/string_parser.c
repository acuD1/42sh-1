/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 21:17:49 by cempassi          #+#    #+#             */
/*   Updated: 2019/04/19 17:15:53 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <fcntl.h>

void	flush_string(t_parser *parse)
{
	int		index;
	t_token *token;

	parse->state = P_STRING_FLUSH;
	index = ft_stcksize(&parse->stack);
	parse->process.av = (char **)malloc(sizeof(char *) * (index + 1));
	parse->process.av[index] = NULL;
	while (--index >= 0)
	{
		token = ft_stckpop(&parse->stack);
		parse->process.av[index] = token->data;
		free(token);
	}
}

void	flush_redirect(t_parser *parse)
{
	t_token	*token;
	char	*filename;

	token = ft_stckpop(&parse->stack);
	filename = token->data;
	free(token);
	token = ft_stckpop(&parse->stack);
	if (((t_token*)ft_stcktop(&parse->stack))->type == E_IO_NUMBER)
	{
		free(ft_stckpop(&parse->stack));
		*parse->fd = open(filename, parse->oflags, 644);
	}
	else if (token->type == E_GREAT || token->type == E_DGREAT)
			parse->process.fdout = open(filename, parse->oflags, 644);
	else
	{
		parse->process.fdin = open(filename, parse->oflags, 644);
		//CONTROL ERROR HERE;
	}
	free(token);
}

void	filename_state(t_parser *parse)
{
	parse->state = P_FILENAME;
	ft_stckpush(&parse->stack, &parse->token, sizeof(t_token));
	get_token(parse);
}

void	string_parser(t_parser *parse)
{
	parse->state = P_STRING;
	ft_stckpush(&parse->stack, &parse->token, sizeof(t_token));
	get_token(parse);
}
