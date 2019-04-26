/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_logger.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 23:38:09 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/26 14:28:24 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "21sh.h"
#include "libft.h"
#include "log.h"
#include "ft_printf.h"

void			log_print(t_registry *reg, char *importance, char *message, ...)
{
	va_list args;
	int		fd;

	if (reg == NULL)
			return ;
	fd = -1;
	fd = ft_atoi(get_intern_var((reg), INT_DBG_FD));
	if (!fd)
			fd = -1;
	if (fd < 1)
	{
		if (ft_strbeginswith(importance, "[CRITICAL]")
				|| ft_strbeginswith(importance, "[ERROR]"))
		{
			ft_dprintf(2, "%s\t- ", importance);
			va_start(args, message);
			ft_vdprintf(message, args, fd);
			va_end(args);
		}
		return ;
	}
	ft_dprintf(fd, "%s\t- ", importance);
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
			home_path = ft_itoa(-1);
			add_internal(reg, INT_DBG_FD, home_path);
			ft_strdel(&home_path);
			ft_dprintf(2, "[ERROR] - Could not fetch home variable.\n");
			return ;
		}

		ft_asprintf(&log_path, "%s/%s", home_path, INT_DBG_FILE);
		debug_fd = open(log_path, O_RDWR | O_APPEND | O_CREAT | O_NOFOLLOW, 0600);
		if (debug_fd < 0)
			return ;
		char *tmp = ft_itoa(debug_fd);
		if (add_internal(reg, INT_DBG_FD, tmp) == -1)
		{
			ft_strdel(&tmp);
			return ;
		}
		ft_strdel(&tmp);
		ft_dprintf(debug_fd, "---------------------------------\n");
		ft_dprintf(debug_fd, "[INFO] - Starting shell\n");
		ft_strdel(&log_path);
	}
	else
	{
		home_path = ft_itoa(-1);
		add_internal(reg, INT_DBG_FD, home_path);
		ft_strdel(&home_path);
	}
}
