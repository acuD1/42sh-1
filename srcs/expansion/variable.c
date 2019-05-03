/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 00:58:53 by cempassi          #+#    #+#             */
/*   Updated: 2019/05/04 01:07:53 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#include "parser.h"

static char	*variable_replace(t_list *lst, char *str)
{
	char		*expanded;
	char		*data;
	uint32_t	i;

	if (*str == '\0')
		return (str);
	expanded = NULL;
	i = ft_strcspn(str, EXP_INTERUPT);
	str[i] = character_swap(str[i]);
	data = get_data(lst, str);
	str[i] = character_swap('\0');
	if (i == 0)
		ft_asprintf(&expanded,"$%s", str);
	else if (data != NULL)
		ft_asprintf(&expanded, "%s%s", data, str + i);
	else
		ft_asprintf(&expanded, "%s", str + i);
	return (expanded);
}

char		*variable_concat(t_list *lst, char **str, int i)
{
	char	*expanded;
	char	*holder;

	holder = NULL;
	expanded = variable_replace(lst, *str + i + 1);
	ft_asprintf(&holder, "%.*s%s", i, str, expanded);
	ft_strdel(&expanded);
	ft_strdel(str);
	return (holder);
}

char		*variable_expansion(t_parser *parse, char *str)
{
	t_quote		quote;
	uint32_t	i;

	i = 0;
	quote = 0;
	while (str[i] != '\0')
	{
		if (ft_strchr("\'\"", str[i]) != NULL)
			quote = select_quoting(quote, str[i]);
		if (str[i] == '$')
		{
			if(ft_strchr(EXP_INTERUPT, str[i + 1]) || str[i + 1] == '\0')
				++i;
			else if (quote != QUOTE_SINGLE)
				str = variable_concat(parse->env, &str, i);
		}
		else
			++i;
	}
	return (str);
}
