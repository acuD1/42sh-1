/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filename_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 04:47:14 by cempassi          #+#    #+#             */
/*   Updated: 2019/05/06 16:17:04 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "unistd.h"

void	filename_parser(t_parser *parse)
{
	if (parse->token.type == E_SPSTRING)
		parse->token.data = string_expansion(parse, parse->token.data);
	if (parse->state == P_IO_REDIRECT)
		parse->state = P_IO_FILENAME;
	else if (parse->token.type == E_SPSTRING)
		parse->state = P_SPFILENAME;
	else
		parse->state = P_FILENAME;
	check_filename(parse);
	get_token(parse);
}

void	flush_redirect_and(t_parser *parse)
{
	char			*filedesc;
	int				fd;
	unsigned int	action;
	t_type			type;

	parse->state = P_REDIRECT_FLUSH_AND;
	action = 0;
	filedesc = pop_token_data(&parse->stack);
	fd = ft_atoi(filedesc);
	ft_strdel(&filedesc);
	type = pop_token_type(&parse->stack);
	action |= parse->special_case & TO_CLOSE ? FD_CLOSE : FD_DUP;
	parse->special_case ^= TO_CLOSE;
	if (type == E_LESSAND)
		generate_filedesc(parse, fd, STDIN_FILENO, action | FD_WRITE);
	else
	{
		generate_filedesc(parse, fd, STDERR_FILENO, action | FD_WRITE);
		generate_filedesc(parse, fd, STDOUT_FILENO, action | FD_WRITE);
	}
}

void	dup_move_parser(t_parser *parse)
{
	if ((parse->token.data = string_expansion(parse, parse->token.data)))
	{
		if(filename_validate(parse, parse->token.data))
			ft_stckpush(&parse->stack, &parse->token, sizeof(t_token));
		else
		{
			parse->state = P_FILENAME;
			ft_stckpush(&parse->stack, &parse->token, sizeof(t_token));
		}
		get_token(parse);
	}
	else
	{
		ft_strdel(&parse->token.data);
		error_parser(parse);
	}
}

void	io_dup_move_parser(t_parser *parse)
{
	parse->token.type = E_STRING;
	if ((parse->token.data = string_expansion(parse, parse->token.data)))
	{
		if (filename_validate(parse, parse->token.data))
			ft_stckpush(&parse->stack, &parse->token, sizeof(t_token));
		else
			ft_strdel(&parse->token.data);
		get_token(parse);
	}
	else
	{
		ft_strdel(&parse->token.data);
		error_parser(parse);
	}
}
