/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 00:58:53 by cempassi          #+#    #+#             */
/*   Updated: 2019/05/02 02:31:40 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#include "parser.h"

char	character_swap(char swapped)
{
	static char previous = '\0';
	char		c;

	c = previous;
	previous = swapped;
	return (c);
}

char	*expansion(t_list *lst, char *str)
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

char	*expand_string(t_list *lst, char *str)
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
			expanded = expansion(lst, &str[i + 1]);;
			ft_asprintf(&holder, "%.*s%s", i, str, expanded);
			ft_strdel(&str);
			str = holder;
		}
		else
			++i;
	}
	return (str);
}
