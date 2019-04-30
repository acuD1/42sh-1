/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 14:57:46 by cempassi          #+#    #+#             */
/*   Updated: 2019/04/30 16:33:37 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "21sh.h"
#include "parser.h"

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
		parse->process.fd.in = fd;
	else
	{
		if (token->type == E_GREATAND || token->type == E_DGREATAND)
			parse->process.fd.err = fd;
		parse->process.fd.out = fd;
	}
	free(token);
	ft_strdel(&filename);
}

void	redirect_parser(t_parser *parse)
{
	parse->state = P_REDIRECT;
	if (parse->token.type == E_GREAT || parse->token.type == E_GREATAND)
		parse->oflags = O_RDWR + O_CREAT + O_TRUNC;
	else if (parse->token.type == E_DGREAT || parse->token.type == E_DGREATAND)
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

void	io_redirect_parser(t_parser *parse)
{
	parse->state = P_IO;
	ft_stckpush(&parse->stack, &parse->token, sizeof(t_token));
	get_token(parse);
}
