/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_logger.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 23:38:09 by skuppers          #+#    #+#             */
/*   Updated: 2019/02/25 11:47:11 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#include "libft.h"
#include "log.h"
#include "ft_printf.h"

static char		*log_fetch_importance(int imp)
{
	char		*str;
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
	str = ft_strjoinfree(str, COLOR_WHITE, 1);
	str = ft_strjoinfree(str, "[", 1);
	str = ft_strjoinfree(str, ft_itoa((int)time), 3);
	str = ft_strjoinfree(str, "] - ", 1);
	return (str);
}

void			log_print(t_registry *reg, int importance, char *message, ...)
{
	va_list args;
	char	*str;

	if (reg->debug_fd < 1)
		return ;
	str = log_fetch_importance(importance);
	ft_printf_fd(reg->debug_fd, str);
	ft_strdel(&str);

	va_start(args, message);
	ft_printf_va(reg->debug_fd, message, args);
	va_end(args);
}

void	init_debug_logger(t_registry *reg)
{
	if (reg->arguments->opt_d)
		reg->debug_fd = 2;//debug to fd->2
	else if (reg->workspace_avaible)
	{
		reg->debug_fd = 2; // Temporary placeholder
		//open file descriptor to std log file
		//keep it open until shell exit
		// registry->debug-fd = X;
	}
	else
		reg->debug_fd = -1;
}
