/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_mode.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 16:05:30 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/27 15:47:41 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "log.h"
#include "interface_functions.h"

int16_t			set_term_behavior(t_registry *shell)
{
	struct termios	term;

	if ((tcgetattr(STDIN_FILENO, &term)) == FAILURE)
	{
		log_print(shell, LOG_ERROR, "Tcgetattr failed fetching info.\n");
		return (FAILURE);
	}
	shell->interface.orig_mode = ft_memalloc(sizeof(struct termios));
	ft_memcpy(shell->interface.orig_mode, &term, sizeof(struct termios));
	term.c_lflag &= ~(ICANON);
	term.c_lflag &= ~(ECHO);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	shell->interface.term_mode = ft_memalloc(sizeof(struct termios));
	ft_memcpy(shell->interface.term_mode, &term, sizeof(struct termios));
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == FAILURE)
	{
		log_print(shell, LOG_ERROR, "Tcsetattr failed setting params.\n");
		return (-2);
	}
	return (SUCCESS);
}

int16_t			restore_term_behavior(t_registry *shell)
{
	if (tcsetattr(STDIN_FILENO, TCSANOW, shell->interface.orig_mode) == FAILURE)
	{
		log_print(shell, LOG_ERROR, "Tcsetattr failed setting params.\n");
		return (-2);
	}
	free(shell->interface.term_mode);
	free(shell->interface.orig_mode);
	return (SUCCESS);
}
