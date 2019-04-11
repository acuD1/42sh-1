/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 10:15:15 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/11 18:54:20 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOG_H
# define LOG_H

#include <time.h>
#include "21sh.h"

#define LOG_OK "[OK]"
#define	LOG_INFO "[INFO]"
#define	LOG_WARNING "[WARNING]"
#define	LOG_ERROR "[ERROR]"
#define	LOG_CRITICAL "[CRITICAL]"

void	log_print(t_registry *reg, char *importance, char *message, ...);
void	init_debug_logger(t_registry *reg);
#endif
