/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_interface_config.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 23:53:07 by skuppers          #+#    #+#             */
/*   Updated: 2019/03/01 11:14:53 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"
#include "log.h"
#include "21sh.h"
#include "line_edit.h"

/*
 *		Retrieving the terminal type, to load the appropriate termcaps database.
 */
int		init_termcaps_database(t_registry *reg)
{
	char			*term_name;

	if ((term_name = getenv("TERM")) == NULL)
	{
		log_print(reg, LOG_ERROR, "Terminal not found.\n");
		return(-1);
	}
	if ((tgetent(NULL, term_name)) == -1)
	{
		log_print(reg, LOG_ERROR, "Tgetent failed.\n");
		return (-1);
	}
	log_print(reg, LOG_OK, "Reached targeting terminal and termcaps database.\n");
	return (0);
}

/*
 *		Retrieving the terminal attributes and setting them to the desired parameters
 *		The original attributes have to be set back at exit.
 */
int		init_terminal_behavior(t_registry *reg, t_interface_registry *itf_reg)
{
	struct termios	t_term;
	struct termios	orig_term;

	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO))
	{
		if ((tcgetattr(STDIN_FILENO, &t_term)) == -1)
		{
			log_print(reg, LOG_ERROR, "Tcgetattr failed fetching info.\n");
			return (-1);
		}
		else
		{
			ft_memcpy(&orig_term, &t_term, sizeof(t_term));
			itf_reg->orig_term = &orig_term;
			log_print(reg, LOG_OK, "Saved initial terminal behavior.\n");
		}
	}
	else
	{
		log_print(reg, LOG_ERROR, "STDIN or STDOUT is not a valid tty.\n");
		return (-1);
	}
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

void	restore_original_term_behavior(t_registry *sh_reg, t_interface_registry *itf_reg)
{
	if (tcsetattr(STDIN_FILENO, TCSANOW, itf_reg->orig_term) == -1)
		log_print(sh_reg, LOG_ERROR, "Failed to restore original term behavior.\n");
}

/*
 *		Try to load all nessesary termcaps sequences and store them
 *		in the appropriate structure. Handle errors accordingly.
 */

/*
 *		Storing the corresponding keycodes for each used key.
 */
int		setup_keycodes(t_interface_registry *itf_reg)
{
	init_ak_keycodes(itf_reg);
	return (0);
}

/*
 *		Linking the appropriate actions to the appropriate keys.
 *		Used at startup and when the keymap file is changed.
 */
int		link_actions_to_keys(t_interface_registry *itf_reg)
{
	//init_termcap_actions
	init_termcap_actions(itf_reg->tc_call);
	return (0);
}

static t_interface_registry *create_interface_registry(t_registry *shell_registry)
{
	t_interface_registry *itf_reg;

	if (!(itf_reg = malloc(sizeof(t_interface_registry))))
	{
		log_print(shell_registry, LOG_ERROR, "Interface registry could not be allocated.\n");
		return (NULL);
	}
	ft_memset(itf_reg, 0, sizeof(t_interface_registry));
	return (itf_reg);
}

t_interface_registry *init_line_edition(t_registry *reg)
{
	t_interface_registry *itf_reg;

	if ((itf_reg = create_interface_registry(reg)) == NULL)
		return (NULL);
	else
		log_print(reg, LOG_OK, "Interface registry created.\n");

	if (init_termcaps_database(reg) != 0)
	{
		log_print(reg, LOG_CRITICAL, "Termcap database not found!\n");
		return (NULL);
	}
	if (init_terminal_behavior(reg, itf_reg) != 0)
	{
		log_print(reg, LOG_CRITICAL, "Terminal could not be initialised.\n");
		return (NULL);
	}

	if ((itf_reg->termcaps = init_termcap_calls(reg)) == NULL)
		return (NULL);
	else
		log_print(reg, LOG_OK, "Termcap registry created.\n");

	setup_keycodes(itf_reg);

	link_actions_to_keys(itf_reg);

	if ((itf_reg->clipboard = allocate_clipboard(reg)) == NULL)
		return (NULL);
	else
		log_print(reg, LOG_INFO, "Clipboard initialized.\n");

	if(itf_reg->clipboard == NULL)
		log_print(reg, LOG_ERROR, "Clipboard failed.\n");

	log_print(reg, LOG_OK, "Line edition initialized.\n");
	return (itf_reg);
}
