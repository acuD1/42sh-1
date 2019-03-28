/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_logger.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 23:38:09 by skuppers          #+#    #+#             */
/*   Updated: 2019/03/26 15:27:56 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#include "libft.h"
#include "log.h"
#include "ft_printf.h"

static char		*log_fetch_importance(int imp)
{
	char		*str;
	char		*msg;
	char		*tmp;
	clock_t		time;

	time = clock();
	if (imp == LOG_OK)
		str = ft_strjoin(COLOR_GREEN, "[OK]");
	else if (imp == LOG_INFO)
		str = ft_strjoin(COLOR_WHITE, "[INFO]");
	else if (imp == LOG_WARNING)
		str = ft_strjoin(COLOR_YELLOW, "[WARNING]");
	else if (imp == LOG_ERROR)
		str = ft_strjoin(COLOR_ORANGE, "[ERROR]");
	else if (imp == LOG_CRITICAL)
		str = ft_strjoin(COLOR_RED, "[CRITICAL]");
	else
		str = ft_strjoin("[DEBUG]","[UNDEFINED]");
	msg = NULL;
	tmp = ft_itoa((int)time);
	ft_asprintf(&msg, "%s%s[%s]", str, COLOR_WHITE, tmp);
	ft_strdel(&(tmp));
	ft_strdel(&(str));
	return (msg);
}

void			log_print(t_registry *reg, int importance, char *message, ...)
{
	va_list args;
	char	*str;

//	if (reg == NULL || reg->debug_fd < 1)
//		return ;
	(void)reg;
	str = log_fetch_importance(importance);
	ft_dprintf(2, "%s", str);
	ft_strdel(&str);

	va_start(args, message);
	ft_vdprintf(message, args, 2);
	va_end(args);
}

void	init_debug_logger(t_registry *reg)
{
	(void)reg;
	/*
	 * Check if -d is activated
	 * Check if path is accessible.
	 * Debug only to log file.
	 */

}
