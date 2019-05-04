/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 21:48:28 by cempassi          #+#    #+#             */
/*   Updated: 2019/05/04 21:51:15 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "parser.h"
#include "interface_functions.h"

static int	check_delimiter(char **delimiter, char *line, int fd)
{
	if (ft_strequ(line, *delimiter) == TRUE)
	{
		close(fd);
		ft_putchar('\n');
		ft_strdel(delimiter);
		return (SUCCESS);
	}
	return (FAILURE);
}

static int	write_heredoc(char **line, int fd, t_type type, t_parser *parse)
{
	int		trim;

	trim = 0;
	if (type == E_DLESSDASH)
		trim = ft_strspn(*line, " \t");
	*line = variable_expansion(parse, *line);
	ft_putendl_fd(*line + trim, fd);
	ft_strdel(line);
	return (0);
}

void		heredoc_delimiter(t_parser *parse)
{
	if (parse->state == P_HEREDOC_REDIRECT)
		parse->state = P_HEREDOC_DELIMITER;
	else
		parse->state = P_IO_HEREDOC_DELIMITER;
	if (g_shell->is_interactive == FALSE)
	{
		ft_dprintf(2,"21sh: Here documents only in interractive mode\n");
		error_parser(parse);
	}
	parse->token.type = E_STRING;
	ft_stckpush(&parse->stack, &parse->token, sizeof(t_token));
	get_token(parse);
}

void		io_heredoc_parser(t_parser *parse)
{
	char		*line;
	char		*delimiter;
	t_type		type;
	char		*io;
	int			fd[2];

	parse->state = P_HEREDOC;
	pipe(fd);
	line = NULL;
	delimiter = pop_token_data(&parse->stack);
	type = pop_token_type(&parse->stack);
	io  = pop_token_data(&parse->stack);
	generate_filedesc(parse, fd[0], ft_atoi(io), FD_DUP | FD_WRITE);
	ft_strdel(&io);
	while (invoke_sub_prompt(g_shell, &line, INT_PS4) == SUCCESS)
	{
		if (check_delimiter(&delimiter, line, fd[1]) == SUCCESS)
			return ;
		else
			write_heredoc(&line, fd[1], type, parse);
		ft_strdel(&line);
	}
	ft_strdel(&line);
	error_parser(parse);
}

void		heredoc_parser(t_parser *parse)
{
	char		*line;
	char		*delimiter;
	t_type		type;
	int			fd[2];

	parse->state = P_HEREDOC;
	line = NULL;
	pipe(fd);
	delimiter = pop_token_data(&parse->stack);
	type = pop_token_type(&parse->stack);
	generate_filedesc(parse, fd[0], STDIN_FILENO, FD_DUP | FD_WRITE);
	while (invoke_sub_prompt(g_shell, &line, INT_PS4) == SUCCESS)
	{
		if (check_delimiter(&delimiter, line, fd[1]) == SUCCESS)
			return ;
		else
			write_heredoc(&line, fd[1], type, parse);
		ft_strdel(&line);
	}
	ft_strdel(&line);
	error_parser(parse);
}
