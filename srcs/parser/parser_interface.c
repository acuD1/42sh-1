/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_interface.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 17:01:44 by cempassi          #+#    #+#             */
/*   Updated: 2019/04/19 01:32:41 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	parse_error(t_parser *parse)
{
	ft_printf("Error on token type %d\n",parse->token.type);
	parse->state = P_ERROR;
}

char	**list_to_tab(t_list *lst)
{
	char	**tab;
	int		index;
	int		len;

	index = 0;
	len = ft_lstlen(lst);
	tab = malloc(sizeof(char *) * len + 1);
	while (index < len)
	{
		tab[index++] = ft_strdup(lst->data);
		lst = lst->next;
	}
	tab[index] = NULL;
	return (tab);
}

void	separator_parser(t_parser *parse)
{
	parse->state = P_SEPARATOR;
	get_token(parse);
}

void	stop_parser(t_parser *parse)
{
	parse->state = P_STOP;
}

void	end_parser(t_parser *parse)
{
	parse->state = P_END;
}
