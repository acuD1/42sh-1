/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 00:58:53 by cempassi          #+#    #+#             */
/*   Updated: 2019/05/02 20:15:15 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#include "parser.h"

static char	*variable_replace(t_list *lst, char *str)
{
	char		*expanded;
	char		*data;
	uint32_t	i;

	expanded = NULL;
	i = ft_strcspn(str, EXP_INTERUPT);
	str[i] = character_swap(str[i]);
	data = get_data(lst, str);
	str[i] = character_swap('\0');
	if (data != NULL)
		ft_asprintf(&expanded, "%s%s", data, str + i);
	else
		ft_asprintf(&expanded, "%s", str + i);
	return (expanded);
}

char		*variable_expansion(t_parser *parse, char *str)
{
	char		*expanded;
	char		*holder;
	uint32_t	i;
	t_quote		quote;

	i = 0;
	quote = 0;
	while (str[i] != '\0')
	{
		holder = NULL;
		if (ft_strchr("\'\"", str[i]) != NULL)
			quote = select_quoting(quote, str[i]);
		if (str[i] == '$' && str[i + 1] != '\0' && quote != QUOTE_SINGLE)
		{
			expanded = variable_replace(parse->env, &str[i + 1]);
			ft_asprintf(&holder, "%.*s%s", i, str, expanded);
			ft_strdel(&str);
			str = holder;
		}
		else
			++i;
	}
	return (str);
}
