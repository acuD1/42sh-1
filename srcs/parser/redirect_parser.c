/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 14:57:46 by cempassi          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2019/04/29 13:57:06 by nrechati         ###   ########.fr       */
=======
/*   Updated: 2019/04/29 15:39:54 by cempassi         ###   ########.fr       */
>>>>>>> develop
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
	size_t	stcksize;

	parse->state = P_REDIRECT_FLUSH;
	token = ft_stckpop(&parse->stack);
	filename = token->data;
	free(token);
	token = ft_stckpop(&parse->stack);
	stcksize = ft_stcksize(&parse->stack);
	if (stcksize != 0 && ((t_token*)ft_stcktop(&parse->stack))->type == E_IO_NUMBER)
	{
		free(ft_stckpop(&parse->stack));
	}
	else if (token->type == E_GREAT || token->type == E_DGREAT)
		parse->process.fd.out = open(filename, parse->oflags, 0644);
	else if ((parse->process.fd.in = open(filename, parse->oflags, 0644) < 0))
		error_parser(parse);
	free(token);
	ft_strdel(&filename);
}

void	redirect_parser(t_parser *parse)
{
	parse->state = P_REDIRECT;
	if (parse->token.type == E_GREAT)
	{
		parse->oflags = O_RDWR + O_CREAT + O_TRUNC;
	}
	else if (parse->token.type == E_DGREAT)
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
