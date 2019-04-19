/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 14:57:46 by cempassi          #+#    #+#             */
/*   Updated: 2019/04/19 17:21:12 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <fcntl.h>

void	redirect_parser(t_parser *parse)
{
	parse->state = P_SUFFIX_REDIRECT;
	if (parse->token.type == E_GREAT)
		parse->oflags = O_WRONLY + O_CREAT + O_TRUNC;
	else if (parse->token.type == E_DGREAT)
		parse->oflags = O_WRONLY + O_CREAT + O_APPEND;
	else if (parse->token.type == E_LESS)
		parse->oflags = O_RDONLY;
	ft_stckpush(&parse->stack, &parse->token, sizeof(t_token));
	get_token(parse);
}

void	io_redirect_parser(t_parser *parse)
{
	if (ft_strchr("012", *parse->token.data))
	{
		parse->state = P_IO;
		if (*parse->token.data == '0')
			parse->fd = &parse->process.fdin;
		else if (*parse->token.data == '1')
			parse->fd = &parse->process.fdout;
		else if (*parse->token.data == '2')
			parse->fd = &parse->process.fderror;
	}
	else
		error_parser(parse);
}
