/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 14:06:27 by nrechati          #+#    #+#             */
/*   Updated: 2019/04/27 14:03:27 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "21sh.h"
#include "builtin.h"

static int		get_env(t_list **alst, char **env)
{
	int i;

	i = 0;
	while (env[i] != NULL)
	{
		if (f_create_node(alst, env[i]) == FAILURE)
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
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
		if (!option->cmd || parse_arg(index + 2, av, option) == FAILURE)
			return (FAILURE);
	}
	else if (ft_strequ(av[index], "--rcfile") == TRUE)
	{
		option->rcfile = 1;
		if (!av[index + 1] || av[index + 1][0] == '-')
			ft_printf("USAGE ./21sh [-rcfile]PATH\n");
		else
			option->path = ft_strdup(av[index + 1]);
		if (option->path == FALSE || parse_arg(index + 2, av, option) == FAILURE)
			return (FAILURE);
	}
	else if (parse_arg(index + 1, av, option) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

int				parse_arg(int index, char **av, t_opt *option)
{
	if (!av[index])
		return (SUCCESS);
	if (av[index][0] != '-')
	{
		ft_printf("USAGE ./21sh [-vdh][--help][--norc][--rcfile]PATH[-c]CMD\n");
		return (FAILURE);
	}
	if (ft_strchr(av[index], 'h') || ft_strequ(av[index], "--help") == TRUE)
		option->h = 1;
	if (ft_strchr(av[index], 'v') || ft_strequ(av[index], "--version") == TRUE)
		option->v = 1;
	if (ft_strchr(av[index], 'd'))
		option->d = 1;
	if (ft_strequ(av[index], "--norc") == TRUE)
	{
		option->norc = 1;
		if (parse_arg(index + 1, av, option) == FAILURE)
			return (FAILURE);
	}
	return (fill_opt(index, av, option));
}

int				launch_sh(char **av, char **env, t_registry *registry)
{
	t_opt		option;
	t_list		*env_lst;
	t_list		*var_lst;

	env_lst = NULL;
	var_lst = NULL;
	ft_bzero(&option, sizeof(t_opt));
	if (parse_arg(1, av, &option) == FAILURE)
	{
		ft_strdel(&(option.cmd));
		ft_strdel(&(option.path));
		return (FAILURE);
	}
	if (get_env(&env_lst, env) == FAILURE)
		return (FAILURE);
	registry->env = env_lst;
	registry->intern = var_lst;
	registry->option = option;
	registry->bin_hashmap = ft_hmap_init(4096);
	registry->blt_hashmap = ft_hmap_init(16);
	return (hash_blt(registry, NULL));
}

/*
**	ft_print_hashmap(&(registry->bin_hashmap));
**	ft_print_hashmap_p(&(registry->blt_hashmap));
*/
