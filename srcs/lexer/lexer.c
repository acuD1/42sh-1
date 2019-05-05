/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 14:23:19 by ffoissey          #+#    #+#             */
/*   Updated: 2019/05/05 04:35:47 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "struct.h"

int			create_token_data(t_lexer *machine)
{
	char	*holder;

	holder = NULL;
	if(machine->buffer_index == BUFFER - 2)
	{
		machine->buffer[machine->buffer_index++] = *machine->input;
		if (machine->data == NULL)
			machine->data = ft_strdup(machine->buffer);
		else
		{
			if (ft_asprintf(&holder,"%s%s", machine->data, machine->buffer) < 0)
			ft_strdel(&machine->data);
			machine->data = holder;
			return (-1);
		}
		ft_bzero(&machine->buffer, BUFFER);
		machine->buffer_index = 0;
	}
	else
		machine->buffer[machine->buffer_index++] = *machine->input;
	return (0);
}

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
