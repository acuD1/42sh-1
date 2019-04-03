/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 14:06:27 by nrechati          #+#    #+#             */
/*   Updated: 2019/04/03 12:54:06 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "21sh.h"

static int		get_env(t_list **alst, char **env)
{
	int i;

	i = 0;
	while (env[i] != NULL)
	{
		if (!f_create_node(alst, env[i]))
			return (0);
		i++;
	}
	return (1);
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
		ft_printf("USAGE ./21sh [-vdh][--help][--norc][--rcfile]PATH[-c]CMD\n");
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

int				launch_sh(int ac, char **av, char **env, t_registry *registry)
{
	t_opt		option;
	t_list		*env_lst;
	t_list		*var_lst;

	(void)ac;
	env_lst = NULL;
	var_lst = NULL;
	ft_bzero(&option, sizeof(t_opt));
	if (!parse_arg(1, av, &option))
	{
		ft_strdel(&(option.cmd));
		ft_strdel(&(option.path));
		return (0);
	}
	if (!get_env(&env_lst, env))
		return (0);
	registry->env = env_lst;
	registry->intern = var_lst;
	registry->option = option;
	return (1);
}
