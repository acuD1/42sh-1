/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_interface_config.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 23:53:07 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/27 15:48:23 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "log.h"
#include "interface_functions.h"

t_registry	*g_shell_registry;

static int8_t		fetch_terminal_info(t_registry *shell)
{
	char			*term_name;

	if ((term_name = getenv("TERM")) == NULL)
		add_internal(shell, INT_TERM, INT_TERM_DFLT_VALUE);
	else
		add_internal(shell, INT_TERM, term_name);
	if (term_name == NULL || (tgetent(NULL, term_name)) == -1)
	{
		log_print(shell, LOG_ERROR, "Tgetent failed.\n");
		return (FAILURE);
	}
	log_print(shell, LOG_OK,
			"Reached targeting terminal and termcaps database.\n");
	return (SUCCESS);
}
/*
static t_interface	*create_interface(t_registry *shell)
{
	t_interface *itf;

	if (!(itf = malloc(sizeof(t_interface))))
	{
		log_print(shell, LOG_ERROR,
				"Interface registry could not be allocated.\n");
		return (NULL);
	}
	ft_memset(itf, 0, sizeof(t_interface));
	return (itf);
}
*/
static int8_t		fill_interface_related_internals(t_registry *reg)
{
	if (add_internal(reg, INT_PS1, INT_PS1_VALUE) == FAILURE)
		return (FAILURE);
	if (add_internal(reg, INT_PS2, INT_PS2_VALUE) == FAILURE)
		return (FAILURE);
	if (add_internal(reg, INT_PS3, INT_PS3_VALUE) == FAILURE)
		return (FAILURE);
	if (add_internal(reg, INT_PS4, INT_PS4_VALUE) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

int8_t load_interface(t_registry *shell)
{
	int8_t			op_worked;
	//if ((itf = create_interface(shell)) == NULL)
	//	return (NULL);
	if (fetch_terminal_info(shell) == FAILURE)
		return (FAILURE);
	if ((init_termcap_calls(&shell->interface.termcaps)) == FAILURE)
		return (FAILURE);
// pas consistent
	setup_keycodes(&shell->interface);
	link_actions_to_keys(shell);
	fill_interface_related_internals(shell);
	if ((op_worked = set_term_behavior(shell)) != 0)
	{
		if (op_worked == -2)
			restore_term_behavior(shell);
		return (FAILURE);
	}
	if ((shell->interface.clip = allocate_clipboard(shell)) == NULL)
		return (FAILURE);
	log_print(shell, LOG_OK, "Line edition initialized.\n");
	shell->interface.history_head = NULL;
	shell->interface.hist_ptr = NULL;
	return (SUCCESS);
}
