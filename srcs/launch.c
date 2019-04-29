/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 14:06:27 by nrechati          #+#    #+#             */
/*   Updated: 2019/04/29 06:49:37 by skuppers         ###   ########.fr       */
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
		option->command = TRUE;
		if (option->command_str != NULL)
			free(option->command_str);
		if (!av[index + 1] || av[index + 1][0] == '-')
			ft_printf("USAGE ./21sh [-c]CMD\n");
		else
			option->command_str = ft_strdup(av[index + 1]);
		if (!option->command_str || parse_arg(index + 2, av, option) == FAILURE)
			return (FAILURE);
	}
//	else if (ft_strequ(av[index], "--rcfile") == TRUE)
//	{
//		option->rcfile = 1;
//		if (!av[index + 1] || av[index + 1][0] == '-')
//			ft_printf("USAGE ./21sh [-rcfile]PATH\n");
//		else
//			option->path = ft_strdup(av[index + 1]);
//		if (option->path == FALSE || parse_arg(index + 2, av, option) == FAILURE)
//			return (FAILURE);
//	}
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
		option->help = TRUE;
	if (ft_strchr(av[index], 'v') || ft_strequ(av[index], "--version") == TRUE)
		option->version = TRUE;
	if (ft_strchr(av[index], 'd'))
		option->debug = TRUE;
//	if (ft_strequ(av[index], "--norc") == TRUE)
//	{
//		option->norc = 1;
//	if (parse_arg(index + 1, av, option) == FAILURE)
//		return (FAILURE);
//	}
	return (fill_opt(index, av, option));
}

int				set_environment(t_registry *shell, char **av, char **env)
{
	t_opt		option;
	t_list		*env_lst;
	t_list		*var_lst;

	env_lst = NULL;
	var_lst = NULL;
	ft_bzero(&option, sizeof(t_opt));
	if (parse_arg(1, av, &option) == FAILURE)
	{
		ft_strdel(&(option.command_str));
//		ft_strdel(&(option.path));
		return (FAILURE);
	}
	if (get_env(&env_lst, env) == FAILURE)
		return (FAILURE);
	shell->env = env_lst;
	shell->intern = var_lst;
	shell->option = option;
	shell->bin_hashmap = ft_hmap_init(4096);
	shell->blt_hashmap = ft_hmap_init(16);
	//wtf
	return (hash_blt(shell, NULL));
}

/*
**	ft_print_hashmap(&(registry->bin_hashmap));
**	ft_print_hashmap_p(&(registry->blt_hashmap));
*/
