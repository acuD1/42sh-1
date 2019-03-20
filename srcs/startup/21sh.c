/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   21sh.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 10:41:54 by skuppers          #+#    #+#             */
/*   Updated: 2019/03/20 13:57:17 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"
#include "21sh.h"
#include "log.h"
#include "startup.h"

void				shell_invoke_interactive(t_registry *shell_registry)
{
	t_interface_registry *itf_registry;

	itf_registry = init_line_edition(shell_registry);
	if (itf_registry != NULL)
	{
		launch_shell_prompt(shell_registry, itf_registry);
		//restore_original_term_behavior(shell_registry, itf_registry);
		free_interface_registry(itf_registry);
		free(itf_registry);
	}
	else
		log_print(shell_registry, LOG_CRITICAL, "Line edition failed, shuting down.\n");
}

int		main(int ac, char **av, char **environ)
{

	(void)ac;
	(void)av;
	(void)environ;

	shell_invoke_interactive(NULL);

	return (0);
}
