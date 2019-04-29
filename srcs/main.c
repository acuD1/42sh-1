/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 13:19:49 by nrechati          #+#    #+#             */
/*   Updated: 2019/04/27 16:35:05 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "21sh.h"
#include "log.h"
#include "interface_functions.h"
#include "parser.h"
#include "resolve.h"

static int		init_shell(t_registry *shell)
{
	init_debug_logger(shell);
	print_opt(shell);

	init_parser(&shell->parser);
	shell->parser.env = shell->env;
	generate_graph(shell);
	return (SUCCESS);	
}

int8_t		execution_pipeline(t_registry *shell, char *command)
{
	if (lexer_parser(&shell->parser, shell->graph, command) == SUCCESS)
	{
		launch_job(shell, shell->parser.job_list);
		ft_lstdel(&shell->parser.job_list, delete_job);
		return (SUCCESS);
	}
	else
	{
		// parse error handling
		return (FAILURE);
	}
	
}

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
	}
	else
	{
		command = ((shell->option.command == TRUE) 
				? shell->option.command_str : read_input(STDIN_FILENO));
		//		ft_dprintf(1, "CMD:\n|%s|\n", command);
		execution_pipeline(shell, command);
	}
}

int		main(int ac, char **av, char **env)
{
	t_registry		shell;
	//char 			*command;

	(void)ac;

	ft_bzero(&shell, sizeof(t_registry));

	if (set_environment(&shell, av, env) == FAILURE)
		return (FAILURE);

	if (init_shell(&shell) == FAILURE)
		return (FAILURE);

	g_shell = &shell;

	launch_shell(&shell);	

	// exit routines
	// Clean interface if neccessary
	// Clean all environment variables
	// Clean all intern variables
	return (SUCCESS);
}
