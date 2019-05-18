/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_mode.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 16:05:30 by skuppers          #+#    #+#             */
/*   Updated: 2019/05/18 14:46:22 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <termios.h>
#include <unistd.h>

static inline uint64_t alloc_otmode(t_registry *shell, struct termios *term)
{
    if ((shell->interface.orig_mode = ft_memalloc(sizeof(struct termios)))
        == NULL)
        return (CRITICAL_ERROR);
    ft_memcpy(shell->interface.orig_mode, &term, sizeof(struct termios));
    return (SUCCESS);
}

static inline uint64_t alloc_ntmode(t_registry *shell, struct termios *term)
{
    if ((shell->interface.term_mode = ft_memalloc(sizeof(struct termios)))
        == NULL)
        return (CRITICAL_ERROR);
    ft_memcpy(shell->interface.term_mode, &term, sizeof(struct termios));
    return (SUCCESS);
}

uint64_t    set_terminal_mode(t_registry *shell)
{
    struct termios	term;

    if ((tcgetattr(STDIN_FILENO, &term)) == FAILURE)
        return (CRITICAL_ERROR | TERMMDE_FAIL);

    if (alloc_otmode(shell, &term) != SUCCESS)
		return (CRITICAL_ERROR | TERMMDE_FAIL | MALLOC_FAIL);

    term.c_lflag &= ~(ICANON);
	term.c_lflag &= ~(ECHO);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;

    if ((tcsetattr(STDIN_FILENO, TCSANOW, &term)) == FAILURE)
        return (CRITICAL_ERROR | TERMMDE_FAIL);

    if (alloc_ntmode(shell, &term) != SUCCESS)
		return (CRITICAL_ERROR | TERMMDE_FAIL | MALLOC_FAIL);

    return (SUCCESS);
}

int8_t			restore_term_behavior(t_registry *shell)
{
	if (tcsetattr(STDIN_FILENO, TCSANOW, shell->interface.orig_mode) == FAILURE)
		return (FAILURE);
	ft_free(shell->interface.term_mode);
	ft_free(shell->interface.orig_mode);
	return (SUCCESS);
}
