/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 14:57:46 by cempassi          #+#    #+#             */
/*   Updated: 2019/04/19 22:29:08 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <fcntl.h>

void	flush_redirect(t_parser *parse)
{
	t_token	*token;
	char	*filename;
	size_t	stcksize;

	parse->state = P_REDIRECT_FLUSH;
	token = ft_stckpop(&parse->stack);
	filename = token->data;
	free(token);
	token = ft_stckpop(&parse->stack);
	stcksize = ft_stcksize(&parse->stack);
	if (stcksize && ((t_token*)ft_stcktop(&parse->stack))->type == E_IO_NUMBER)
	{
		free(ft_stckpop(&parse->stack));
		*parse->fd = open(filename, parse->oflags, 0644);
	}
	else if (token->type == E_GREAT || token->type == E_DGREAT)
			parse->process.fdout = open(filename, parse->oflags, 0644);
	else if ((parse->process.fdin = open(filename, parse->oflags, 0644) < 0))
			error_parser(parse);
	free(token);
}

void	redirect_parser(t_parser *parse)
{
	parse->state = P_REDIRECT;
	if (parse->token.type == E_GREAT)
	{
		parse->oflags = O_RDWR + O_CREAT + O_TRUNC;
		ft_printf("Flags = %b\n", parse->oflags);
	}
	else if (parse->token.type == E_DGREAT)
		parse->oflags = O_RDWR + O_CREAT + O_APPEND;
	else if (parse->token.type == E_LESS)
		parse->oflags = O_RDONLY;
	ft_stckpush(&parse->stack, &parse->token, sizeof(t_token));
	get_token(parse);
}

void	heredoc_parser(t_parser *parse)
{
	parse->state = P_HEREDOC;
}

void	io_redirect_parser(t_parser *parse)
{
	if (ft_strchr("012", *parse->token.data))
	{
		parse->state = P_IO;
		if (*parse->token.data == '0')
			parse->fd = &parse->process.fdin;
		else if (*parse->token.data == '1')
			parse->fd = &parse->process.fdout;
		else if (*parse->token.data == '2')
			parse->fd = &parse->process.fderror;
	ft_stckpush(&parse->stack, &parse->token, sizeof(t_token));
	get_token(parse);
	}
	else
		error_parser(parse);
}
