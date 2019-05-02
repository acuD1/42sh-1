/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_debug.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 16:42:18 by ffoissey          #+#    #+#             */
/*   Updated: 2019/05/01 01:18:42 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_registry	*g_shell;

void		print_token_debug(t_token *token)
{
	if (token->type == E_STRING || token->type == E_SPSTRING )
		ft_printf("\033[37m         --------\n         |   %5s   | data [%s]\n         --------\n",
				g_shell->grammar[token->type], token->data);
	else
		ft_printf("\033[37m         --------\n         |   %c   |\n         --------\n",
				g_shell->grammar[token->type]);
}

void		print_arrow_debug(int which)
{
	if (which == 0)
		ft_printf("\033[33m            ||\n            vv\n\033[0m");
	else if (which == 1)
		ft_printf("\033[34m            ||\n            up\n            ||\n            vv\n\033[0m");
	else
		ft_printf("\033[36m            ||\n           down\n            ||\n            vv\n\033[0m");
}

void		print_error_debug(enum e_type type, int which)
{
	if (which == 0)
		ft_printf("\033[31m ==> ERROR: token type %d is not possible\n\033[0m", type);
	else if (which == 1)
		ft_printf("\033[31m ==> ERROR: miss token type %d\n\033[0m", type);
	else
		ft_printf("\033[31m ==> ERROR: parsing error\n\033[0m");
}

void		print_result_debug(int which)
{
	if (which == 0)
		ft_printf("\033[32m         --------\n         |  OK  |\n         --------\n\n\033[0m");
	else
		ft_printf("\033[31m         --------\n         |  KO  |\n         --------\n\n\033[0m");
}
