/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_interface_config.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 23:53:07 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/03 12:01:28 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "log.h"
#include "line_edit.h"

int							init_termcaps_database(t_registry *reg)
{
	char			*term_name;

	if ((term_name = getenv("TERM")) == NULL)
	{
		log_print(reg, LOG_ERROR, "Terminal not found.\n");
		return (-1);
	}
	if ((tgetent(NULL, term_name)) == -1)
	{
		log_print(reg, LOG_ERROR, "Tgetent failed.\n");
		return (-1);
	}
	log_print(reg, LOG_OK,
			"Reached targeting terminal and termcaps database.\n");
	return (0);
}

int							init_terminal_behavior(
				t_registry *reg, t_interface_registry *itf_reg)
{
	struct termios	t_term;
	struct termios	*orig_term;

	if (!isatty(STDIN_FILENO) || !isatty(STDOUT_FILENO))
	{
		log_print(reg, LOG_ERROR, "STDIN or STDOUT is not a valid tty.\n");
		return (-1);
	}
	if ((tcgetattr(STDIN_FILENO, &t_term)) == -1)
	{
		log_print(reg, LOG_ERROR, "Tcgetattr failed fetching info.\n");
		return (-1);
	}
	if ((orig_term = malloc(sizeof(struct termios))) == NULL)
	{
		log_print(reg, LOG_CRITICAL, "Could not allocate memory for saving termIOS structure.\n");
		return (-1);
	}
	ft_memcpy(orig_term, &t_term, sizeof(t_term));

	itf_reg->orig_term = orig_term;
	log_print(reg, LOG_OK, "Saved initial terminal behavior.\n");
	t_term.c_lflag &= ~(ICANON);
	t_term.c_lflag &= ~(ECHO);
	t_term.c_cc[VMIN] = 1;
	t_term.c_cc[VTIME] = 0;
	if (isatty(STDIN_FILENO))
		if (tcsetattr(STDIN_FILENO, TCSANOW, &t_term) == -1)
			log_print(reg, LOG_ERROR, "Tcsetattr failed setting params.\n");
	itf_reg->new_term = &t_term;
	return (0);
}

void						restore_original_term_behavior(
				t_registry *sh_reg, t_interface_registry *itf_reg)
{
	if (tcsetattr(STDIN_FILENO, TCSANOW, itf_reg->orig_term) == -1)
		log_print(sh_reg, LOG_ERROR,
				"Failed to restore original term behavior.\n");
}

static t_interface_registry	*create_interface_registry(
				t_registry *shell_registry)
{
	t_interface_registry *itf_reg;

	if (!(itf_reg = malloc(sizeof(t_interface_registry))))
	{
		log_print(shell_registry, LOG_ERROR,
				"Interface registry could not be allocated.\n");
		return (NULL);
	}
	ft_memset(itf_reg, 0, sizeof(t_interface_registry));
	return (itf_reg);
}

int		fill_interface_related_internals(t_registry *reg)
{
	add_internal(reg, INT_READ_SZ, INT_READ_SZ_VALUE);
	add_internal(reg, INT_CLIPBOARD_SZ, INT_CLIPBOARD_SZ_VALUE);
	add_internal(reg, INT_PS1, INT_PS1_VALUE);
	add_internal(reg, INT_PS2, INT_PS2_VALUE);
	add_internal(reg, INT_IFS, INT_IFS_VALUE);
	add_internal(reg, INT_ESCAPE_SEQ, INT_ESCAPE_SEQ_VALUE);
	return (0);
}

t_interface_registry		*init_line_edition(t_registry *reg)
{
	t_interface_registry *itf_reg;

	if ((itf_reg = create_interface_registry(reg)) == NULL)
		return (NULL);
	if (init_termcaps_database(reg) != 0)
		return (NULL);
	if (init_terminal_behavior(reg, itf_reg) != 0)
		return (NULL);
	if ((itf_reg->termcaps = init_termcap_calls(reg)) == NULL)
		return (NULL);
	setup_keycodes(itf_reg);
	link_actions_to_keys(itf_reg);

	fill_interface_related_internals(reg);
	itf_reg->sh_reg = reg;
	if ((itf_reg->clipboard = allocate_clipboard(reg)) == NULL)
		return (NULL);
	log_print(reg, LOG_OK, "Line edition initialized.\n");
	return (itf_reg);
}
