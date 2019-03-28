/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 10:15:15 by skuppers          #+#    #+#             */
/*   Updated: 2019/03/28 18:42:30 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOG_H
# define LOG_H

#include <time.h>
#include "21sh.h"

enum importance {
	LOG_OK,
	LOG_INFO,
	LOG_WARNING,
	LOG_ERROR,
	LOG_CRITICAL
};

void	log_print(t_registry *reg, int importance, char *message, ...);
void	init_debug_logger(t_registry *reg);
#endif
