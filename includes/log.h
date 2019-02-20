/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 10:15:15 by skuppers          #+#    #+#             */
/*   Updated: 2019/02/20 12:57:56 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOG_H
# define LOG_H

# define COLOR_WHITE 	"\x1b[0m"
# define COLOR_GREEN 	"\x1b[92m"
# define COLOR_YELLOW 	"\x1b[93m"
# define COLOR_ORANGE	"\x1b[35m"
# define COLOR_RED		"\x1b[31m"

#include <time.h>

enum importance {
	LOG_OK,
	LOG_INFO,
	LOG_WARNING,
	LOG_ERROR,
	LOG_CRITICAL
};

void	log_print(int importance, char *message, ...);

#endif
