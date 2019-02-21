/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   21sh.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 10:41:54 by skuppers          #+#    #+#             */
/*   Updated: 2019/02/21 14:21:55 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#include "log.h"
#include "startup.h"

//Initialise termcaps directives
/*		if (init_line_edition() == -1)
		{
		log_print(LOG_CRITICAL,"Line edition setup failed. See logs for more info.\n");
		return (-1);
		}
		else
		log_print(LOG_OK, "Line edition succesfully initialised.\n");

//Main prompt
while (1)
{
char *user_input_string = prompt();
start_execution_pipeline(user_input_string);
}
}*/

void				shell_invoke(t_registry *reg)
{
	char	*input_command;

	if (reg->arguments->opt_c)
	{
//		execute_shell_command(reg->arguments->c_param);
	}
	else if (reg->arguments->opt_i)
	{
		if (init_line_edition(reg) == 0)
			launch_shell_prompt(reg);
		else
		{

		}
	}
	else if (reg->arguments->opt_h)
	{
//		print_shell_usage();
	}
	else
	{
		log_print(LOG_ERROR, "Shell invokation is incomplete.\n");
	}
}

static t_registry	*create_shell_registry(void)
{
	t_registry *new;

	if (!(new = malloc(sizeof(t_registry))))
		return (NULL);
	ft_memset(new, 0, sizeof(t_registry));
	return (new);
}

int		main(int ac, char **av, char **environ)
{
	t_registry	*shell_registry;

	if ((shell_registry = create_shell_registry()) == NULL)
	{
		ft_putstr("The shell registry could not be allocated!\n");
		return (-1);
	}

	// TODO: REWORK ARGUMENTS PARSING
	shell_registry->arguments = 	 parse_arguments(ac, av);

	//TODO: Finish env handling (deletion/rewriting etc...) + unit-testing
	shell_registry->environment =	 parse_environment(environ);

	//TODO: Code this function lol
	load_config_files(shell_registry);

	/* If workspace is not avaible, this returns 0,
	 * default keymaps are used, history is not saved or loaded aswell as
	 * hashtables and 42rc files */

//	shell_registry->workspace_avaible = init_workspace(shell_registry);

	/* debug to log file is default
	 * if log file is not avaible, dont log
	 * unless -d is specified so debug fd->2 */
//	init_debug_logger(shell_registry);

	//	prepare_data_structures();

	//	prepare_runtime_signals();

	shell_invoke(shell_registry);

	return (0);
}
