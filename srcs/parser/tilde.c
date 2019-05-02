/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 12:57:21 by cempassi          #+#    #+#             */
/*   Updated: 2019/05/02 13:36:28 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#include "parser.h"

char	*tilde_expansion(t_list *env, char *str)
{
	char	*expanded;

	expanded = NULL;
	if (ft_strequ(str, "~"))
		expanded = get_data(env, "HOME");
	else if (ft_strequ(str, "~+"))
		expanded = get_data(env, "PWD");
	else if (ft_strequ(str, "~-"))
		expanded = get_data(env, "PWD");
	return (expanded);
}

char	*tilde(t_list *env, char *str)
{
	char	*expanded;
	char	*holder;
	int		i;

	i = 0;
	holder = NULL;
	if (str[0] == '~')
	{
		i = ft_strcspn(str, "/");
		str[i] = character_swap(str[i]);
		expanded = tilde_expansion(env, str);
		str[i] = character_swap('\0');
		ft_asprintf(&holder, "%s%s", expanded, str + i);
		ft_strdel(&str);
		str = holder;
	}
	return (str);
}
