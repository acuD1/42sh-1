/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 14:57:46 by cempassi          #+#    #+#             */
/*   Updated: 2019/05/03 18:57:58 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "21sh.h"
#include "parser.h"
#include "interface_functions.h"

int		find_stdout_redirect(void *data, void *to_find)
{
	t_filedesc *fd;

	fd = data;
	return (fd->second == *(int *)to_find? 1 : 0);
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
		error_parser(parse);
	else if (token->type == E_LESS)
		generate_filedesc(parse, fd, STDIN_FILENO, FD_DUP | FD_WRITE);
	else
	{
		if (token->type == E_GREATAND || token->type == E_ANDDGREAT)
			generate_filedesc(parse, fd, STDERR_FILENO, FD_DUP | FD_WRITE);
		else if (token->type == E_ANDGREAT)
			generate_filedesc(parse, fd, STDERR_FILENO, FD_DUP | FD_WRITE);
		generate_filedesc(parse, fd, STDOUT_FILENO, FD_DUP | FD_WRITE);
	}
	free(token);
	ft_strdel(&filename);
}

void	redirect_parser(t_parser *parse)
{
	parse->state = P_REDIRECT;
	if (parse->token.type == E_GREAT)
		parse->oflags = O_RDWR + O_CREAT + O_TRUNC;
	if (parse->token.type == E_GREATAND || parse->token.type == E_ANDGREAT)
		parse->oflags = O_RDWR + O_CREAT + O_TRUNC;
	else if (parse->token.type == E_DGREAT || parse->token.type == E_ANDDGREAT)
		parse->oflags = O_RDWR + O_CREAT + O_APPEND;
	else if (parse->token.type == E_LESS)
		parse->oflags = O_RDONLY;
	else if (parse->token.type == E_DLESSDASH)
		parse->state = P_HEREDOC_REDIRECT;
	ft_stckpush(&parse->stack, &parse->token, sizeof(t_token));
	get_token(parse);
}

void	pipe_parser(t_parser *parse)
{
	t_list		*node;
	int			fd[2];
	int			stdo;

	stdo = 1;
	parse->state = pipe(fd) ? P_ERROR : P_PIPE;
	if (parse->state == P_ERROR)
		return ;
	if (ft_lstfind(parse->process.fd, &stdo, find_stdout_redirect))
		close(fd[1]);
	else
		generate_filedesc(parse, fd[1], STDOUT_FILENO, FD_DUP | FD_WRITE);
	parse->process.env = ft_lsttotab(parse->env, variable_to_str);
	node = ft_lstnew(&parse->process, sizeof(t_process));
	ft_lstaddback(&parse->job.process_list, node);
	init_process(&parse->process);
	generate_filedesc(parse, fd[0], STDIN_FILENO, FD_DUP | FD_WRITE);
	get_token(parse);
}

int		write_heredoc(t_parser *parse, char **line, int fd, t_type type)
{
	int		trim;

	trim = 0;
	*line = variable_expansion(parse, *line);
	if (type == E_DLESSDASH)
		trim = ft_strspn(*line, " \t");
	ft_putstr_fd(*line + trim, fd);
	ft_strdel(line);
	return (0);
}

void	heredoc_parser(t_parser *parse)
{
	int			fd;
	char		*line;
	t_type		type;

	line = NULL;
	fd = open("/tmp/42herdoc", O_RDWR + O_CREAT + O_TRUNC);
	parse->state = P_HEREDOC;
	type = ((t_token *)ft_stcktop(&parse->stack))->type;
	free(ft_stckpop(&parse->stack));
	parse->token.data = string_expansion(parse, parse->token.data);
	while(invoke_sub_prompt(g_shell, &line, INT_PS4) == SUCCESS)
	{
		if (ft_strequ(line, parse->token.data) == TRUE)
		{
			generate_filedesc(parse, fd, STDIN_FILENO, FD_DUP | FD_WRITE);
			ft_strdel(&line);
			ft_strdel(&parse->token.data);
			return ;
		}
		write_heredoc(parse, &line, fd, type);
	}
	ft_strdel(&line);
	ft_strdel(&parse->token.data);
	error_parser(parse);
}
