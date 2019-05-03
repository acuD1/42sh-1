/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filename_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 04:47:14 by cempassi          #+#    #+#             */
/*   Updated: 2019/05/03 04:48:38 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	filename_parser(t_parser *parse)
{
	ft_stckpush(&parse->stack, &parse->token, sizeof(t_token));
	get_token(parse);
	parse->state = P_FILENAME;
}

void	special_filename_parser(t_parser *parse)
{
	parse->state = P_SPFILENAME;
	parse->token.type = E_STRING;
	if ((parse->token.data = string_expansion(parse, parse->token.data)))
	{
		ft_stckpush(&parse->stack, &parse->token, sizeof(t_token));
		get_token(parse);
	}
}

void	io_filename_parser(t_parser *parse)
{
	parse->state = P_IO_FILENAME;
	parse->token.type = E_STRING;
	if ((parse->token.data = string_expansion(parse, parse->token.data)))
	{
		ft_stckpush(&parse->stack, &parse->token, sizeof(t_token));
		get_token(parse);
	}
}

int		io_filename_validate(t_parser *parse, char *str)
{
	int		len;

	if (ft_strcheck(str, ft_isdigit) == 1)
	{
		parse->state = P_IO_DUP;
		return (1);
	}
	len = ft_strlen(str);
	str[len - 1] = character_swap(str[len - 1]);
	if(ft_strcheck(str, ft_isdigit) == 1)
	{
		str[len - 1] = character_swap('\0');
		if (str[len - 1] == '-')
		{
			parse->state = P_IO_MOVE;
			return (1);
		}
	}
	str[len - 1] = character_swap('\0');
	error_parser(parse);
	return (0);
}

void	io_dup_move_parser(t_parser *parse)
{
	parse->token.type = E_STRING;
	if ((parse->token.data = string_expansion(parse, parse->token.data)))
	{
		if (io_filename_validate(parse, parse->token.data))
		{
			ft_stckpush(&parse->stack, &parse->token, sizeof(t_token));
			get_token(parse);
		}
	}
}
