/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 12:57:21 by cempassi          #+#    #+#             */
/*   Updated: 2019/05/02 19:34:27 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#include "parser.h"
#include <unistd.h>

static char	*user_home(const char *str)
{
	char	*path;

	path = NULL;
	ft_asprintf(&path,"/Users/%s", str);
	if (access(path, F_OK) != SUCCESS)
	{
		ft_strdel(&path);
		return (NULL);
	}
	return (path);
}

static char	*tilde_expansion(t_parser *parse, const char *str)
{
	char	*expanded;

	expanded = NULL;
	if (ft_strequ(str, "~") == TRUE)
		expanded = get_data(parse->env, "HOME");
	else if (ft_strequ(str, "~+") == TRUE)
		expanded = get_data(parse->env, "PWD");
	else if (ft_strequ(str, "~-") == TRUE)
	{
		if ((expanded = get_data(parse->env, "OLDPWD")) != NULL)
			return (expanded);
		parse->valid = -1;
		error_parser(parse);
	}
	else if ((expanded = user_home(str + 1)) == NULL)
	{
		parse->valid = -2;
		error_parser(parse);
	}
	return (expanded);
}

char		*tilde(t_parser *parse, char *str)
{
	char		*expanded;
	char		*holder;
	uint32_t	i;

	i = 0;
	holder = NULL;
	if (ft_strnequ(str, "~/", 2) == FALSE && ft_strequ(str, "~") == FALSE)
		return (str);
	if (str[0] == '~')
	{
		i = ft_strcspn(str, "/");
		str[i] = character_swap(str[i]);
		expanded = tilde_expansion(parse, str);
		str[i] = character_swap('\0');
		ft_asprintf(&holder, "%s%s", expanded, str + i);
		ft_strdel(&str);
		str = holder;
	}
	return (str);
}
