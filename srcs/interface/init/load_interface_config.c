/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_interface_config.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 23:53:07 by skuppers          #+#    #+#             */
/*   Updated: 2019/02/19 14:21:11 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"
#include "log.h"

/*
 *		Retrieving the terminal type, to load the appropriate termcaps database.
 */
int		init_termcaps_database(void)
{
	char			*term_name;

	if ((term_name = getenv("TERM")) == NULL)
	{
		log_print(LOG_ERROR, "Terminal not found.\n");
		return(-1);
	}
	if ((tgetent(NULL, term_name)) == -1)
	{
		log_print(LOG_ERROR, "Tgetent failed.\n");
		return (-1);
	}
	log_print(LOG_OK, "Reached targeting terminal and termcaps database.\n");
	return (0);
}

/*
 *		Retrieving the terminal attributes and setting them to the desired parameters
 *		The original attributes have to be set back at exit.
 */
int		init_terminal_behavior(void)
{
	struct termios	t_term;

	if (isatty(STDIN_FILENO))
	{
		if ((tcgetattr(STDIN_FILENO, &t_term)) == -1)
		{
			log_print(LOG_ERROR, "Tcgetattr failed saving info.\n");
		}
		else
			log_print(LOG_OK, "terminal.\n");
	}
	else
	{
		log_print(LOG_ERROR, "STDIN is not a valid tty.\n");
		return (-1);
	}
	t_term.c_lflag &= ~(ICANON);
	t_term.c_lflag &= ~(ECHO);
	t_term.c_cc[VMIN] = 1;
	t_term.c_cc[VTIME] = 0;

	if (isatty(STDIN_FILENO))
		if (tcsetattr(STDIN_FILENO, TCSANOW, &t_term) == -1)
			log_print(LOG_ERROR, "Tcsetattr failed setting params.\n");

	return (0);
}

/*
 *		Try to load all nessesary termcaps sequences and store them
 *		in the appropriate structure. Handle errors accordingly.
 */
int		load_termcaps()
{
	//init_termcaps_calls
	init_termcap_calls();
}

/*
 *		Storing the corresponding keycodes for each used key.
 */
int		setup_keycodes()
{

	init_ak_keycodes();
}

/*
 *		Linking the appropriate actions to the appropriate keys.
 *		Used at startup and when the keymap file is changed.
 */
int		link_actions_to_keys()
{
	//init_termcap_actions
	init_termcap_actions(tc_call);
}




int		init_line_edition(void)
{
	if (init_termcaps_database() == -1)
	{
		log_print(LOG_CRITICAL, "Termcap database not found!\n");
		return (-1);
	}





	if (!(g_clipboard = ft_vctnew(0)))
		log_print(LOG_ERROR, "Clipboard failed.\n");
	else
		log_print(LOG_INFO, "Clipboard initialized.\n");



	log_print(LOG_OK, "Line edition initialized.\n");
}
