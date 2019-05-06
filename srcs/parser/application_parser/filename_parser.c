/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filename_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 04:47:14 by cempassi          #+#    #+#             */
/*   Updated: 2019/05/06 16:55:10 by cempassi         ###   ########.fr       */
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
