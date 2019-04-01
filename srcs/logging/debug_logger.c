/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_logger.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 23:38:09 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/01 15:19:33 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "21sh.h"
#include "libft.h"
#include "log.h"
#include "ft_printf.h"
#include <stdlib.h>

static char		*log_fetch_importance(int imp)
{
	char		*str;
	char		*msg;
	char		*tmp;
	clock_t		time;

	str = ft_strnew(16);
	time = clock();
	if (imp == LOG_OK)
		ft_strcpy(str, "[OK]");
	else if (imp == LOG_INFO)
		ft_strcpy(str, "[INFO]");
	else if (imp == LOG_WARNING)
		ft_strcpy(str, "[WARNING]");
	else if (imp == LOG_ERROR)
		ft_strcpy(str, "[ERROR]");
	else if (imp == LOG_CRITICAL)
		ft_strcpy(str, "[CRITICAL]");
	else
		ft_strcpy(str, "[UNDEFINED]");
	msg = NULL;
	tmp = ft_itoa((int)time);
	ft_asprintf(&msg, "%s[%s]", str, tmp);
	ft_strdel(&(tmp));
	ft_strdel(&(str));
	return (msg);
}

void			log_print(t_registry *reg, int importance, char *message, ...)
{
	va_list args;
	char	*str;

	if (reg == NULL)
			return ;
	str = log_fetch_importance(importance);
	if (reg->debug_fd < 0)
	{
		if (ft_strbeginswith(str, "[CRITICAL]")
				|| ft_strbeginswith(str, "[ERROR]"))
		{
			ft_dprintf(2, "%s\t- ", str);
			ft_strdel(&str);
			va_start(args, message);
			ft_vdprintf(message, args, reg->debug_fd);
			va_end(args);
		}
		return ;
	}
	ft_dprintf(reg->debug_fd, "%s\t- ", str);
	ft_strdel(&str);
	va_start(args, message);
	ft_vdprintf(message, args, reg->debug_fd);
	va_end(args);
}

void	init_debug_logger(t_registry *reg)
{
	/*
	 * Check if -d is activated
	 * Check if path is accessible.
	 * Debug only to log file.
	 */
	int  debug_fd;
	char *home_path;
	char *log_path;

	home_path = NULL;
	log_path = NULL;
	debug_fd = -1;

	// reg.option.d == 1
	if (1)
	{
		if ((home_path = getenv("HOME")) == NULL)
		{
			reg->debug_fd = -1;
			return ;
		}
		// reg->intern->debug_file_name = ".42sh.log"
		ft_asprintf(&log_path, "%s/%s", home_path, ".42sh.log");
		debug_fd = open(log_path, O_RDWR | O_APPEND | O_CREAT | O_NOFOLLOW, 0600);
		if (debug_fd < 0)
			return ;
		reg->debug_fd = debug_fd;
		ft_dprintf(reg->debug_fd, "---------------------------------\n");
		ft_strdel(&log_path);
	}
	else
		reg->debug_fd = -1;
}
