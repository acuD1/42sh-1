/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_redirect_parser.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 04:42:30 by cempassi          #+#    #+#             */
/*   Updated: 2019/05/04 01:04:29 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "21sh.h"
#include "parser.h"

void	io_redirect_flush(t_parser *parse)
{
	char		*filename;
	int			fd;
	int			io_number;
	int			action;

	action = 0;
	parse->state = P_IO_FLUSH;
	filename = pop_token_data(&parse->stack);
	pop_token_type(&parse->stack);
	io_number = ft_atoi(pop_token_data(&parse->stack));
	action |= FD_WRITE | FD_DUP;
	if ((fd = open(filename, parse->oflags, 0644)) < 0)
		error_parser(parse);
	else
		generate_filedesc(parse, fd, io_number, action);
	ft_strdel(&filename);
}

void	io_and_redirect_flush(t_parser *parse)
{
	t_type		type;
	char		*fd;
	char		*io;
	unsigned int action;

	action = 0;
	parse->state = P_IO_FLUSH_AND;
	fd = pop_token_data(&parse->stack);
	type = pop_token_type(&parse->stack);
	io = pop_token_data(&parse->stack);
	action |= ft_strequ(fd, "-") ? FD_CLOSE : FD_DUP;
	generate_filedesc(parse, ft_atoi(fd), ft_atoi(io), action | FD_WRITE);
	ft_strdel(&fd);
	ft_strdel(&io);
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
	else if (parse->token.type == E_DLESS)
		parse->state = P_IO_HEREDOC_REDIRECT;
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
