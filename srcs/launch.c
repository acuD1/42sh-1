/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 14:06:27 by nrechati          #+#    #+#             */
/*   Updated: 2019/05/02 14:54:15 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#include "builtin.h"

static int		set_shlvl(t_list **env_lst)
{
	if (search_data(env_lst, "SHLVL") == SUCCESS)
		change_node(env_lst, "SHLVL"
		, ft_itoa(ft_atoi(get_data(env_lst, "SHLVL")) + 1));
	else
	{
		if (f_create_node(env_lst, "SHLVL=1") == FAILURE)
			return (FAILURE);
	}
	return (SUCCESS);
}

static int8_t	get_env(t_list **alst, char **env)
{
	int i;

	i = 0;
	while (env[i] != NULL)
	{
		if (f_create_node(alst, env[i]) == FAILURE)
			return (FAILURE);
		i++;
	}
	if (set_shlvl(alst) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

static int8_t	shell_option_letter(t_opt *option, char *arg)
{
	if (*arg != '-')
	{
		ft_dprintf(2, "21sh: %c: invalid option\n", *arg);
		return (FAILURE);
	}
	++arg;
	if (*arg == '-')
		return (FAILURE);
	while (*arg != '\0')
	{
		if (*arg == 'h')
			option->option |= HELP_OPT;
		else if (*arg == 'v')
			option->option |= VERSION_OPT;
		else if (*arg == 'd')
			option->option |= DEBUG_OPT;
		else
		{
			ft_dprintf(2, "21sh: -%c: invalid option\n", *arg);
			return (FAILURE);
		}
		++arg;
	}
	return (SUCCESS);
}

static int8_t	shell_option_word(t_opt *option, char *arg)
{
	if (ft_strequ(arg, "--help") == TRUE)
		option->option |= HELP_OPT;
	else if (ft_strequ(arg, "--version") == TRUE)
		option->option |= VERSION_OPT;
	else if (ft_strequ(arg, "--debug") == TRUE)
		option->option |= DEBUG_OPT;
	else
	{
		if (ft_strnequ(arg, "--", 2) == TRUE)
			ft_dprintf(2, "21sh: %s: invalid option\n", arg);
		return (FAILURE);
	}
	return (SUCCESS);
}

static int8_t	parse_arg(char **av, t_opt *option)
{
//////////// MISS --norc and --rcfile
	while (*av != NULL)
	{
		if (ft_strequ(*av, "--") == TRUE)
			return (SUCCESS);
		else if (ft_strequ(*av, "-c") == TRUE)
		{
			option->option |= COMMAND_OPT;
			ft_strdel(&option->command_str);
			av++;
			if (*av == NULL || **av == '-')
			{
				ft_dprintf(2, "21sh: need command after -c option\n", av);
				return (shell_usage());
			}
			option->command_str = ft_strdup(*av);
		}
		else if (shell_option_word(option, *av) == FAILURE)
			if (shell_option_letter(option, *av) == FAILURE)
				return (shell_usage());
		av++;
	}
	return (SUCCESS);
}

int				set_environment(t_registry *shell, char **av, char **env)
{
	if (*av)
	{
		if (parse_arg(av, &shell->option) == FAILURE)
		{
			ft_strdel(&(shell->option.command_str));
			//ft_strdel(&(shell->option.path));
			return (FAILURE);
		}
	}
	if (get_env(&shell->env, env) == FAILURE)
		return (FAILURE);
	shell->bin_hashmap = ft_hmap_init(4096);
	shell->blt_hashmap = ft_hmap_init(32);
	//wtf
	return (hash_blt(shell, NULL));
}

/*
**	ft_print_hashmap(&(registry->bin_hashmap));
**	ft_print_hashmap_p(&(registry->blt_hashmap));
*/
