/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 14:57:46 by cempassi          #+#    #+#             */
/*   Updated: 2019/05/03 01:46:41 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "21sh.h"
#include "parser.h"

void	generate_filedesc(t_parser *parse, int fst, int sec, t_fd_action act)
{
	t_list		*node;
	t_filedesc	fd;

	fd.first = f;
	fd.second = second;
	node = ft_lstnew(&fd, sizeof(t_filedesc));
	ft_lstaddback(&parse->process.fd, node);
}

void	flush_redirect(t_parser *parse)
{
	t_token	*token;
	char	*filename;
	int		fd;

	parse->state = P_REDIRECT_FLUSH;
	token = ft_stckpop(&parse->stack);
	filename = token->data;
	free(token);
	token = ft_stckpop(&parse->stack);
	if ((fd = open(filename, parse->oflags, 0644)) < 0)
	{
		error_parser(parse);
		return ;
	}
	if (token->type == E_LESS)
		generate_filedesc(parse, fd, STDIN_FILENO);
	else
	{
		if (token->type == E_GREATAND || token->type == E_ANDDGREAT)
			generate_filedesc(parse, fd, STDERR_FILENO);
		generate_filedesc(parse, fd, STDOUT_FILENO);
	}
	free(token);
	ft_strdel(&filename);
}

void	redirect_parser(t_parser *parse)
{
	parse->state = P_REDIRECT;
	if (parse->token.type == E_GREAT || parse->token.type == E_GREATAND)
		parse->oflags = O_RDWR + O_CREAT + O_TRUNC;
	else if (parse->token.type == E_DGREAT || parse->token.type == E_ANDDGREAT)
		parse->oflags = O_RDWR + O_CREAT + O_APPEND;
	else if (parse->token.type == E_LESS)
		parse->oflags = O_RDONLY;
	ft_stckpush(&parse->stack, &parse->token, sizeof(t_token));
	get_token(parse);
}

void	pipe_parser(t_parser *parse)
{
	t_list		*node;
	int			fd[2];

	parse->state = pipe(fd) ? P_ERROR : P_PIPE;
	if (parse->state == P_ERROR)
		return ;
	if (parse->process.fd.out == STDOUT_FILENO)
		parse->process.fd.out = fd[1];
	else
		close(fd[1]);
	parse->process.env = ft_lsttotab(parse->env, variable_to_str);
	node = ft_lstnew(&parse->process, sizeof(t_process));
	ft_lstaddback(&parse->job.process_list, node);
	init_process(&parse->process);
	parse->process.fd.in = fd[0];
	get_token(parse);
}

void	heredoc_parser(t_parser *parse)
{
	int			fd[2];
	char		*line;

	line = NULL;
	pipe(fd);
	parse->state = P_HEREDOC;
	while(ft_strequ(line, parse->token.data) == FALSE)
	{

	}
}


void	io_redirect_flush(t_parser *parse)
{
	t_token		*token;
	char		*filename;
	int			fd;
	int			io_number;

	parse->state = P_IO_FLUSH;
	token = ft_stckpop(&parse->stack);
	filename = token->data;
	free(token);
	token = ft_stckpop(&parse->stack);
	io_number = ft_atoi(ft_stcktop(&parse->stack));
	if ((fd = open(filename, parse->oflags, 0644)) < 0)
	{
		error_parser(parse);
		return ;
	}
	if(token->type == E_GREAT || token->type == E_DGREAT)
		generate_filedesc(parse, fd, io_number);
	else if(token->type == E_LESS)
		generate_filedesc(parse, fd, io_number);
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
