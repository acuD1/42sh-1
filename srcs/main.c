/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 13:19:49 by nrechati          #+#    #+#             */
/*   Updated: 2019/04/30 11:15:24 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "21sh.h"
#include "log.h"
#include "interface_functions.h"
#include "parser.h"
#include "resolve.h"

int8_t		shell_usage(void)
{
	ft_dprintf(2, "%s%s\nLong options:%s%s",
					SH21_USAGE_1,
					SH21_USAGE_2,
					SH21_USAGE_LONG_OPTION,
					SH21_USAGE_LONG_OPTION_2);
	return (FAILURE);
}

static int	stdin_build_cmd(t_registry *shell, char *command)
{
	int		i;
	char	*non_interactive_cmd;
	char	**tab;

	i = 1;
	non_interactive_cmd = NULL;
	if ((tab = ft_strsplit(command, "\n")) == FALSE)
		return (FAILURE);
	ft_asprintf(&non_interactive_cmd, "%s", tab[0]);
	while (tab[i] != FALSE)
		ft_asprintf(&non_interactive_cmd, " ; %s", tab[i++]);
	if (non_interactive_cmd == FALSE)
		return (FAILURE);
	execution_pipeline(shell, lexer(non_interactive_cmd));
	free(non_interactive_cmd);
	return (SUCCESS);
}

static void	launch_shell(t_registry *shell)
{
	char	*command;

	if ((shell->option.option & COMMAND_OPT) == FALSE
		&& isatty(STDIN_FILENO) != 0)
	{
		if ((load_interface(shell)) == SUCCESS)
			launch_interface(shell);
		else
			ft_printf("[CRITICAL] - Interface setup failed. See logs.\n");
		unload_interface(&shell->interface);
	}
	else
	{
		command = ((shell->option.option & COMMAND_OPT) != FALSE
				? shell->option.command_str : read_input(STDIN_FILENO));
		if (command != NULL)
		{
			if (stdin_build_cmd(shell, command) == FAILURE)
				ft_dprintf(2, "[CRITICAL] - Malloc error.\n");
		}
		else
			ft_dprintf(2, "[CRITICAL] - No valid input to execute.\n");
	}
}

int			main(int ac, char **av, char **env)
{
	t_registry		shell;

	(void)ac;
	ft_bzero(&shell, sizeof(t_registry));
	g_shell = &shell;
	if (set_environment(&shell, av + 1, env) == FAILURE)
		return (FAILURE);
	if (init_shell(&shell) == FAILURE)
		return (FAILURE);
	launch_shell(&shell);
	// Clean all intern variables
	// Clean all environment variables
	shell_exit_routine(&shell);
	return (SUCCESS);
}
