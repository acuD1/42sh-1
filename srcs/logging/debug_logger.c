/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_logger.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 23:38:09 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/09 19:13:54 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "21sh.h"
#include "libft.h"
#include "log.h"
#include "ft_printf.h"

static char		*log_fetch_importance(int imp)
{
	char		*str;

	str = ft_strnew(16);
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
	return (str);
}

void			log_print(t_registry *reg, int importance, char *message, ...)
{
	va_list args;
	char	*str;
	int		fd;

	if (reg == NULL)
			return ;
	fd = -1;
	fd = ft_atoi(get_intern_var((reg), INT_DBG_FD));
	if (!fd)
			fd = -1;
	str = log_fetch_importance(importance);
	if (fd < 1)
	{
		if (ft_strbeginswith(str, "[CRITICAL]")
				|| ft_strbeginswith(str, "[ERROR]"))
		{
			ft_dprintf(2, "%s\t- ", str);
			ft_strdel(&str);
			va_start(args, message);
			ft_vdprintf(message, args, fd);
			va_end(args);
		}
		return ;
	}
	ft_dprintf(fd, "%s\t- ", str);
	ft_strdel(&str);
	va_start(args, message);
	ft_vdprintf(message, args, fd);
	va_end(args);
}

void	init_debug_logger(t_registry *reg)
{
	int  debug_fd;
	char *home_path;
	char *log_path;

	home_path = NULL;
	log_path = NULL;
	debug_fd = -1;

	if (reg->option.d)
	{
		if ((home_path = get_data(&(reg->env), "HOME")) == NULL)
		{
			add_internal(reg, INT_DBG_FD, ft_itoa(-1));
			ft_dprintf(2, "[ERROR] - Could not fetch home variable.\n");
			return ;
		}

		ft_asprintf(&log_path, "%s/%s", home_path, INT_DBG_FILE);
		debug_fd = open(log_path, O_RDWR | O_APPEND | O_CREAT | O_NOFOLLOW, 0600);
		if (debug_fd < 0)
			return ;
		if (add_internal(reg, INT_DBG_FD, ft_itoa(debug_fd)) == -1)
				return ;
		ft_dprintf(debug_fd, "---------------------------------\n");
		ft_dprintf(debug_fd, "[INFO] - Starting shell\n");
		ft_strdel(&log_path);
	}
	else
		add_internal(reg, INT_DBG_FD, ft_itoa(-1));
}
