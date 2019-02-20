/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   21sh.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 10:41:54 by skuppers          #+#    #+#             */
/*   Updated: 2019/02/20 15:12:25 by skuppers         ###   ########.fr       */
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

static t_registry	*create_shell_registry(void)
{
	t_registry *new;

	if (!(new = malloc(sizeof(t_registry))))
		return (NULL);
	ft_memset(new, 0, sizeof(t_registry));
}

int		main(int ac, char **av, char **environ)
{
	t_registry	*shell_registry;

	if ((shell_registry = create_shell_registry()) == NULL)
	{
		ft_putstr("The shell registry could not be allocated!\n");
		return (-1);
	}

	shell_registry->arguments = 	 parse_arguments(ac, av);

	shell_registry->environment =	 parse_environment(environ);

	/* If workspace is not avaible, this returns 0, debug log is redirected to fd->2
	 * default keymaps are used, history is not saved or loaded aswell as
	 * hashtables and 42rc files.
	 * It will still search for /etc/profile, /etc/paths.d/ and /etc/manpaths */
	shell_registry->workspace_avaible = init_workspace(shell_registry);

//	init_debug_logger(shell_registry);

//	load_config_files();

//	prepare_data_structures();

//	prepare_runtime_signals();

//	shell_invoke(/* non-/-Interactive / login / noprofile */);

	return (0);
}
