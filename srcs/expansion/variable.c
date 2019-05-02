/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 00:58:53 by cempassi          #+#    #+#             */
/*   Updated: 2019/05/02 18:49:50 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#include "parser.h"

char	*variable_replace(t_list *lst, char *str)
{
	char	*expanded;
	char	*data;
	int		i;

	expanded = NULL;
	i = ft_strcspn(str, EXP_INTERUPT);
	str[i] = character_swap(str[i]);
	data = get_data(lst, str);
	str[i] = character_swap('\0');
	if (data)
		ft_asprintf(&expanded, "%s%s", data, str + i);
	else
		ft_asprintf(&expanded, "%s", str + i);
	return (expanded);
}

char	*variable_expansion(t_parser *parse, char *str)
{
	char	*expanded;
	char	*holder;
	int		i;

	i = 0;
	while (str[i])
	{
		holder = NULL;
		if (str[i] == '$' && str[i + 1])
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
