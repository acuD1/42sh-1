/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   21sh.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 10:41:54 by skuppers          #+#    #+#             */
/*   Updated: 2019/03/06 16:17:27 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"
#include "21sh.h"
#include "log.h"
#include "startup.h"

void				shell_invoke(t_registry *shell_registry)
{
	t_interface_registry *itf_registry;

	if (shell_registry->arguments->opt_c)
	{
//		execute_shell_command(reg->arguments->c_param);
	}
	else if (shell_registry->arguments->opt_i)
	{
		itf_registry = init_line_edition(shell_registry);
		if (itf_registry != NULL)
		{
			launch_shell_prompt(shell_registry, itf_registry);
//			restore_original_term_behavior(shell_registry, itf_registry);
			free(itf_registry);
		}
		else
			log_print(shell_registry, LOG_CRITICAL, "Line edition failed, shuting down.\n");
	}
	else if (shell_registry->arguments->opt_h)
	{
//		print_shell_usage();
	}
	else
	{
		log_print(shell_registry, LOG_ERROR, "Shell invokation is incomplete.\n");
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

	/* If posix mode, dont use a workspace, only use bash default files.
	 * default keymaps are used, history is not saved or loaded aswell as
	 * hashtables and 42rc files */
//	if (!shell_registry->arguments->opt_posix)
//		shell_registry->workspace_avaible = init_workspace(shell_registry);
//	else
	shell_registry->workspace_avaible = 0;

	/* debug to log file is default
	 * if log file is not avaible, dont log
	 * unless -d is specified so debug fd->2 */
	init_debug_logger(shell_registry);

	//	prepare_data_structures();

	//	prepare_runtime_signals();

	shell_invoke(shell_registry);

//	cleanup_shell_registry(shell_registry);
	return (0);
}
