/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 14:57:46 by cempassi          #+#    #+#             */
/*   Updated: 2019/05/06 16:31:09 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "21sh.h"
#include "parser.h"

int		find_stdout_redirect(void *data, void *to_find)
{
	t_filedesc *fd;

	fd = data;
	return (fd->second == *(int *)to_find ? 1 : 0);
}

void	flush_redirect(t_parser *parse)
{
	char	*filename;
	t_type	type;
	int		fd;

	parse->state = P_REDIRECT_FLUSH;
	filename = pop_token_data(&parse->stack);
	type = pop_token_type(&parse->stack);
	if ((fd = open(filename, parse->oflags, 0644)) < 0)
	{
		ft_dprintf(2, "21sh: %s: No such file\n", filename);
		error_parser(parse);
	}
	else if (type == E_LESS)
		generate_filedesc(parse, fd, STDIN_FILENO, FD_DUP | FD_WRITE);
	else
	{
		if (type == E_GREATAND || type == E_ANDDGREAT)
			generate_filedesc(parse, fd, STDERR_FILENO, FD_DUP | FD_WRITE);
		else if (type == E_ANDGREAT)
			generate_filedesc(parse, fd, STDERR_FILENO, FD_DUP | FD_WRITE);
		generate_filedesc(parse, fd, STDOUT_FILENO, FD_DUP | FD_WRITE);
	}
	parse->special_case ^= NO_PIPE;
	ft_strdel(&filename);
}

void	redirect_and_parser(t_parser *parse)
{
	parse->state = P_REDIRECT_AND;
	if (parse->token.type == E_GREATAND)
		parse->oflags = O_RDWR + O_CREAT + O_TRUNC;
	else if (parse->token.type == E_LESSAND)
		parse->oflags = O_RDONLY;
	ft_stckpush(&parse->stack, &parse->token, sizeof(t_token));
	get_token(parse);
}

void	redirect_parser(t_parser *parse)
{
	parse->state = P_REDIRECT;
	if (parse->token.type == E_GREAT)
		parse->oflags = O_RDWR + O_CREAT + O_TRUNC;
	else if (parse->token.type == E_DGREAT || parse->token.type == E_ANDDGREAT)
		parse->oflags = O_RDWR + O_CREAT + O_APPEND;
	else if (parse->token.type == E_LESS)
		parse->oflags = O_RDONLY;
	else if (parse->token.type == E_DLESSDASH || parse->token.type == E_DLESS)
		parse->state = P_HEREDOC_REDIRECT;
	if (parse->token.type == E_DLESSDASH)
		parse->special_case ^= HERETRIM;
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
	if (parse->special_case & NO_PIPE)
		close(fd[1]);
	else
		generate_filedesc(parse, fd[1], STDOUT_FILENO, FD_DUP | FD_WRITE);
	node = ft_lstnew(&parse->process, sizeof(t_process));
	ft_lstaddback(&parse->job.process_list, node);
	init_process(&parse->process);
	generate_filedesc(parse, fd[0], STDIN_FILENO, FD_DUP | FD_READ);
	get_token(parse);
}
