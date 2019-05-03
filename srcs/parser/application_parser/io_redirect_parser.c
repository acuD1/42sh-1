/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_redirect_parser.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 04:42:30 by cempassi          #+#    #+#             */
/*   Updated: 2019/05/03 05:44:25 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "21sh.h"
#include "parser.h"

void	io_redirect_flush(t_parser *parse)
{
	t_token		*token;
	char		*filename;
	int			fd;
	int			io_number;
	int			action;

	action = 0;
	parse->state = P_IO_FLUSH;
	token = ft_stckpop(&parse->stack);
	filename = token->data;
	free(token);
	token = ft_stckpop(&parse->stack);
	io_number = ft_atoi(ft_stcktop(&parse->stack));
	action |= token->type == E_LESS ? FD_READ | FD_DUP : FD_WRITE | FD_DUP;
	if ((fd = open(filename, parse->oflags, 0644)) < 0)
		error_parser(parse);
	else
		generate_filedesc(parse, io_number, fd, action);
	free(token);
	token = ft_stckpop(&parse->stack);
	ft_strdel(&filename);
	ft_strdel(&token->data);
	free(token);
}

void	io_and_redirect_flush(t_parser *parse)
{
	t_token		*token;
	t_type		type;
	char		*fd;
	int			io_number;
	unsigned int action;

	action = 0;
	parse->state = P_IO_FLUSH_AND;
	token = ft_stckpop(&parse->stack);
	fd = token->data;
	free(token);
	token = ft_stckpop(&parse->stack);
	type = token->type;
	free(token);
	token = ft_stckpop(&parse->stack);
	io_number = ft_atoi(token->data);
	ft_strdel(&token->data);
	free(token);
	action |= ft_strequ(fd, "-") ? FD_CLOSE : FD_DUP;
	action |=  FD_READ;
	if (type == E_GREATAND)
		generate_filedesc(parse, io_number, ft_atoi(fd), action);
	else
		generate_filedesc(parse, io_number, ft_atoi(fd), action);
	ft_strdel(&fd);
}

void	io_redirect_parser(t_parser *parse)
{
	parse->state = P_IO_REDIRECT;
	if (parse->token.type == E_GREAT)
		parse->oflags = O_RDWR + O_CREAT + O_TRUNC;
	else if (parse->token.type == E_DGREAT)
		parse->oflags = O_RDWR + O_CREAT + O_APPEND;
	else if (parse->token.type == E_LESS)
		parse->oflags = O_RDONLY;
	ft_stckpush(&parse->stack, &parse->token, sizeof(t_token));
	get_token(parse);
}

void	io_redirect_and_parser(t_parser *parse)
{
	parse->state = P_IO_REDIRECT_AND;
	ft_stckpush(&parse->stack, &parse->token, sizeof(t_token));
	get_token(parse);
}

void	io_parser(t_parser *parse)
{
	parse->state = P_IO;
	ft_stckpush(&parse->stack, &parse->token, sizeof(t_token));
	get_token(parse);
}
