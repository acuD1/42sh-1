/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 13:19:49 by nrechati          #+#    #+#             */
/*   Updated: 2019/04/29 14:57:33 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "21sh.h"
#include "log.h"
#include "interface_functions.h"
#include "parser.h"
#include "resolve.h"

static void	launch_shell(t_registry *shell)
{
	char 	*command;

	if (shell->option.command == FALSE
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
		command = ((shell->option.command == TRUE)
				? shell->option.command_str : read_input(STDIN_FILENO));
		if (command != NULL)
			execution_pipeline(shell, command);
		else
			ft_printf("[CRITICAL] - No valid input to execute.\n");
	}
}

int		main(int ac, char **av, char **env)
{
	t_registry		shell;

	(void)ac;
	ft_bzero(&shell, sizeof(t_registry));

	if (set_environment(&shell, av, env) == FAILURE)
		return (FAILURE);

	if (init_shell(&shell) == FAILURE)
		return (FAILURE);

	g_shell = &shell;

	launch_shell(&shell);

	// Clean all intern variables
	// Clean all environment variables
	shell_exit_routine(&shell);

	return (SUCCESS);
}
