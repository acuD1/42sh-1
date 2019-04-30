/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 13:19:49 by nrechati          #+#    #+#             */
/*   Updated: 2019/04/30 10:12:26 by nrechati         ###   ########.fr       */
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
	ft_dprintf(2,"%s%s\nLong options:%s%s",
					SH21_USAGE_1,
					SH21_USAGE_2,
					SH21_USAGE_LONG_OPTION,
					SH21_USAGE_LONG_OPTION_2);
	return (FAILURE);
}

static void	launch_shell(t_registry *shell)
{
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
		//execution_pipeline(shell, lexer(shell->option.command_str));
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
