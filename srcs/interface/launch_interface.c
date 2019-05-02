/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_interface.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 13:29:53 by skuppers          #+#    #+#             */
/*   Updated: 2019/05/02 12:39:32 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "log.h"
#include "lexer.h"
#include "sig.h"
#include "history.h"
#include "21sh.h"
#include "interface_functions.h"
#include <termcap.h>

static void			update_history(t_registry *shell, char *input)
{
	t_history	*new;

	new = create_history_entry(input);
	push_history_entry(&shell->interface.history_head, new);
}

static int8_t		get_input(t_registry *shell, char **input)
{
	*input = prompt(shell);
	if (*input == NULL)
		return (FAILURE);
	else if (**input == '\0')
		return (get_input(shell, input));
	else if (is_eof(*input))
		return (FAILURE);
	return (SUCCESS);
}

static int8_t		launch_shell_prompt(t_registry *shell)
{
	char		*input;

	define_interface_signals();

	if (get_input(shell, &input) == FAILURE)
	{
		cleanup_interface(shell);
		return (FAILURE);
	}
	ft_putchar('\n');
	update_history(shell, input);
	define_ign_signals();
	execution_pipeline(shell, lexer(&shell->lexinfo, input));
	return (SUCCESS);
}

void				launch_interface(t_registry *shell)
{
	log_print(shell, LOG_INFO, "Starting interface.\n");
	while (launch_shell_prompt(shell) == SUCCESS)
		cleanup_interface(shell);
	restore_term_behavior(shell);
}
