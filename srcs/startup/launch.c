/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 14:06:27 by nrechati          #+#    #+#             */
/*   Updated: 2019/04/23 19:09:26 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "21sh.h"

static t_list	*get_env(t_list **alst, char **env)
{
	t_list		*node;
	t_variable	variable;
	size_t		pos;

	if (*env == NULL)
		return (*alst);
	pos = ft_strcspn(*env, "=");
	variable.name = ft_strsub(*env, 0, pos);
	variable.data = ft_strdup(*env + pos + 1);
	if (variable.name == NULL || variable.data == NULL)
		return (NULL);
	if (!(node = ft_lstnew(&variable, sizeof(t_variable))))
		return (NULL);
	ft_lstaddback(alst, node);
	return (get_env(alst, ++env));
}

int				fill_opt(int index, char **av, t_opt *option)
{
	if (ft_strchr(av[index], 'c') && av[index][1] != '-')
	{
		option->c = 1;
		if (option->cmd != NULL)
			free(option->cmd);
		if (!av[index + 1] || av[index + 1][0] == '-')
			ft_printf("USAGE ./21sh [-c]CMD\n");
		else
			option->cmd = ft_strdup(av[index + 1]);
		if (!option->cmd || !parse_arg(index + 2, av, option))
			return (0);
	}
	else if (!ft_strcmp(av[index], "--rcfile"))
	{
		option->rcfile = 1;
		if (!av[index + 1] || av[index + 1][0] == '-')
			ft_printf("USAGE ./21sh [-rcfile]PATH\n");
		else
			option->path = ft_strdup(av[index + 1]);
		if (!option->path || !parse_arg(index + 2, av, option))
			return (0);
	}
	else if (!parse_arg(index + 1, av, option))
		return (0);
	return (1);
}

int				parse_arg(int index, char **av, t_opt *option)
{
	if (!av[index])
		return (1);
	if (av[index][0] != '-')
	{
		ft_printf(USAGE);
		return (0);
	}
	if (ft_strchr(av[index], 'h') || !ft_strcmp(av[index], "--help"))
		option->h = 1;
	if (ft_strchr(av[index], 'v') || !ft_strcmp(av[index], "--version"))
		option->v = 1;
	if (ft_strchr(av[index], 'd'))
		option->d = 1;
	if (!ft_strcmp(av[index], "--norc"))
	{
		option->norc = 1;
		if (!parse_arg(index + 1, av, option))
			return (0);
	}
	if (!fill_opt(index, av, option))
		return (0);
	return (1);
}

int				launch_sh(char **av, char **env, t_registry *shell)
{
	ft_bzero(&shell->option, sizeof(t_opt));
	if (!parse_arg(1, av, &shell->option))
	{
		ft_strdel(&(shell->option.cmd));
		ft_strdel(&(shell->option.path));
		return (0);
	}
	shell->bin_hashmap = ft_hmap_init(2048);
	shell->blt_hashmap = ft_hmap_init(16);
	if (!hash_blt(shell))
		return (0);
	return (get_env(&shell->env, env) ? 0 : -1);
}
