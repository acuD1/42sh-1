/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_interface_config.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 23:53:07 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/26 16:38:29 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "log.h"
#include "line_edit.h"
#include "interface_functions.h"

t_registry	*g_shell_registry;

static uint8_t		fetch_terminal_info(t_registry *shell)
{
	char			*term_name;

	if ((term_name = getenv("TERM")) == NULL)
		add_internal(shell, INT_TERM, INT_TERM_DFLT_VALUE);
	else
		add_internal(shell, INT_TERM, term_name);
	if ((tgetent(NULL, get_intern_var(shell, INT_TERM))) == -1)
	{
		log_print(shell, LOG_ERROR, "Tgetent failed.\n");
		return (-1);
	}
	log_print(shell, LOG_OK,
			"Reached targeting terminal and termcaps database.\n");
	return (0);
}

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

static int8_t		fill_interface_related_internals(t_registry *reg)
{
	add_internal(reg, INT_PS1, INT_PS1_VALUE);
	add_internal(reg, INT_PS2, INT_PS2_VALUE);
	add_internal(reg, INT_PS3, INT_PS3_VALUE);
	add_internal(reg, INT_PS4, INT_PS4_VALUE);
	add_internal(reg, INT_PS5, INT_PS5_VALUE);
	return (0);
}

t_interface			*init_line_edition(t_registry *shell)
{
	t_interface	*itf;
	int8_t		op_worked;

	if ((itf = create_interface(shell)) == NULL)
		return (NULL);
	if (fetch_terminal_info(shell) != 0)
		return (NULL);
	if ((itf->termcaps = init_termcap_calls(shell)) == NULL)
		return (NULL);
	shell->interface = itf;
	setup_keycodes(itf);
	link_actions_to_keys(shell);
	fill_interface_related_internals(shell);
	if ((op_worked = set_term_behavior(shell)) != 0)
	{
		if (op_worked == -2)
			restore_term_behavior(shell);
		return (NULL);
	}
	if ((itf->clip = allocate_clipboard(shell)) == NULL)
		return (NULL);
	log_print(shell, LOG_OK, "Line edition initialized.\n");
	itf->history_head = NULL;
	itf->hist_ptr = NULL;
	g_shell_registry = shell;
	return (itf);
}
