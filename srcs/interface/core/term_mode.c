/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_mode.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 16:05:30 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/23 20:48:58 by cempassi         ###   ########.fr       */
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
	shell->interface.orig_mode = ft_memalloc(sizeof(struct termios));
	ft_memcpy(shell->interface.orig_mode, &term, sizeof(struct termios));
	term.c_lflag &= ~(ICANON);
	term.c_lflag &= ~(ECHO);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	shell->interface.term_mode = ft_memalloc(sizeof(struct termios));
	ft_memcpy(shell->interface.term_mode, &term, sizeof(struct termios));
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == -1)
	{
		log_print(shell, LOG_ERROR, "Tcsetattr failed setting params.\n");
		return (-2);
	}
	return (0);
}

short						restore_term_behavior(t_registry *shell)
{
	if (tcsetattr(STDIN_FILENO, TCSANOW, shell->interface.orig_mode) == -1)
	{
		log_print(shell, LOG_ERROR, "Tcsetattr failed setting params.\n");
		return (-2);
	}
	free(shell->interface.term_mode);
	free(shell->interface.orig_mode);
	return (0);
}
