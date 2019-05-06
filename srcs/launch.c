/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 14:06:27 by nrechati          #+#    #+#             */
/*   Updated: 2019/05/06 12:15:16 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#include "builtin.h"

static int		set_shlvl(t_registry *shell)
{
	char		*shlvl;

	shlvl = get_env_var(shell, "SHLVL");
	if (shlvl == NULL)
		add_env(shell, "SHLVL", "1");
	else
	{
		shlvl = ft_itoa(ft_atoi(shlvl) + 1);
		if (shlvl == NULL)
			return (FAILURE);
		add_env(shell, "SHLVL", shlvl);
		ft_strdel(&shlvl);
	}
	return (SUCCESS);
}

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
	{
		ft_dprintf(2, "[ERROR] - Env malloc failed.\n");
		return (NULL);
	}
	if (!(node = ft_lstnew(&variable, sizeof(t_variable))))
	{
		ft_dprintf(2, "[ERROR] - Env malloc error.\n");
		return (NULL);
	}
	ft_lstaddback(alst, node);
	return (get_env(alst, ++env));
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

static int8_t	shell_option_word(t_opt *option, const char *arg)
{
	if (ft_strequ(arg, "--help") == TRUE)
		option->option |= HELP_OPT;
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

int8_t			set_environment(t_registry *shell, char **av, char **env)
{
	if (*av != NULL)
	{
		if (parse_arg(av, &shell->option) == FAILURE)
		{
			ft_strdel(&(shell->option.command_str));
			return (FAILURE);
		}
	}
	if ((shell->option.option & HELP_OPT) != FALSE)
	{
		shell_usage();
		ft_flush_memory();
		exit(0);
	}
	get_env(&shell->env, env);
	shell->bin_hashmap = ft_hmap_init(4096);
	shell->blt_hashmap = ft_hmap_init(32);
	shell->cur_fd.in = 0;
	shell->cur_fd.out = 1;
	shell->cur_fd.err = 2;
	if (set_shlvl(shell) == FAILURE)
		return (FAILURE);
	return (hash_blt(shell, NULL));
}

/*
**	ft_print_hashmap(&(registry->bin_hashmap));
**	ft_print_hashmap_p(&(registry->blt_hashmap));
*/
