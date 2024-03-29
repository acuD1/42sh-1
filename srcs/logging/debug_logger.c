/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_logger.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <skuppers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 23:38:09 by skuppers          #+#    #+#             */
/*   Updated: 2019/05/07 15:03:04 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "sh21.h"

void			log_print(t_registry *shell, const char *importance,
					const char *message, ...)
{
	va_list args;
	int		fd;

	if (shell == NULL)
		return ;
	fd = -1;
	fd = ft_atoi(get_intern_var((shell), INT_DBG_FD));
	if (fd == STDIN_FILENO)
		fd = -1;
	if (fd < 0)
	{
		if (ft_strbeginswith(importance, "[CRITICAL]") == TRUE
				|| ft_strbeginswith(importance, "[ERROR]") == TRUE)
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

static void		debug_logger_extend(t_registry *shell,
					char *home_path, char *log_path)
{
	char	*tmp;
	int		debug_fd;

	debug_fd = -1;
	if ((home_path = get_data(shell->env, "HOME")) == NULL)
	{
		home_path = ft_itoa(-1);
		add_internal(shell, INT_DBG_FD, home_path);
		ft_strdel(&home_path);
		ft_dprintf(2, "[ERROR] - Could not fetch home variable.\n");
		return ;
	}
	ft_asprintf(&log_path, "%s/%s", home_path, INT_DBG_FILE);
	debug_fd = open(log_path, O_RDWR | O_APPEND | O_CREAT, 0644);
	if (debug_fd < 0)
		return ;
	tmp = ft_itoa(debug_fd);
	if (add_internal(shell, INT_DBG_FD, tmp) == FAILURE)
	{
		ft_strdel(&tmp);
		return ;
	}
	ft_strdel(&tmp);
	ft_strdel(&log_path);
}

void			init_debug_logger(t_registry *shell)
{
	char *home_path;
	char *log_path;

	home_path = NULL;
	log_path = NULL;
	if ((shell->option.option & DEBUG_OPT) != FALSE)
		debug_logger_extend(shell, home_path, log_path);
	else
	{
		home_path = ft_itoa(-1);
		add_internal(shell, INT_DBG_FD, home_path);
		ft_strdel(&home_path);
	}
}
