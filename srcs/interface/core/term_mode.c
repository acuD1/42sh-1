/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_mode.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 16:05:30 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/12 16:28:04 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "log.h"
#include "line_edit.h"
#include "interface_functions.h"

short						set_term_behavior(t_registry *shell)
{
	struct termios	term;

	if ((tcgetattr(STDIN_FILENO, &term)) == -1)
	{
		log_print(shell, LOG_ERROR, "Tcgetattr failed fetching info.\n");
		return (-1);
	}

	// set modes here and simply substract them on exit
	// man termios: ISIG | ICRNL | IXON ??
	term.c_lflag &= ~(ICANON);
	term.c_lflag &= ~(ECHO);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;

	if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == -1)
	{
		log_print(shell, LOG_ERROR, "Tcsetattr failed setting params.\n");
		return (-2);
	}
	return (0);
}

short						restore_term_behavior(t_registry *shell)
{
	struct termios	term;

	if ((tcgetattr(STDIN_FILENO, &term)) == -1)
	{
		log_print(shell, LOG_ERROR, "Tcgetattr failed fetching info.\n");
		return (-1);
	}

	//add same as above here
	term.c_lflag |= ~(ICANON);
	term.c_lflag |= ~(ECHO);

	if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == -1)
	{
		log_print(shell, LOG_ERROR, "Tcsetattr failed setting params.\n");
		return (-2);
	}
	return (0);
}

