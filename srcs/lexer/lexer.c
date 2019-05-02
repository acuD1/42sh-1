/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 14:23:19 by ffoissey          #+#    #+#             */
/*   Updated: 2019/05/02 03:20:32 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "struct.h"

t_list			*lexer(t_lexinfo *info, char *input)
{
	t_lexer	machine;

	if (input == NULL)
		return (NULL);
	while (*input == '\t' || *input == ' ')
		input++;
	if (*input == '\0')
		return (NULL);
	ft_bzero(&machine, sizeof(t_lexer));
	machine.state = L_START;
	machine.last_lexer = E_DEFAULT;
	machine.input = input;
	machine.lexinfo = info;
	while (machine.state != L_FINISH)
		machine.lexinfo->lexing[machine.state](&machine);
	return (machine.tokens);
}
