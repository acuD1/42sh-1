/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 20:16:09 by cempassi          #+#    #+#             */
/*   Updated: 2019/05/02 20:38:14 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	delete_char(char *str)
{
	char	holder;

	while(str[1])
	{
		holder = str[0];
		str[0] = str[1];
		str[1] = holder;
		++str;
	}
	*str = '\0';
}

void	quote_removal(char *str)
{
	t_quote quote;

	quote = 0;
	while(*str)
	{
		if (ft_strchr("\'\"", *str))
			quote = select_quoting(quote, *str);
		if (quote != QUOTE_DOUBLE && *str == '\'')
			delete_char(str);
		else if (quote != QUOTE_SINGLE && *str == '\"')
			delete_char(str);
		++str;
	}
}
