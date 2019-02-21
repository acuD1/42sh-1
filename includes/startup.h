/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   startup.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 14:36:38 by skuppers          #+#    #+#             */
/*   Updated: 2019/02/21 14:57:56 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef H_STARTUP_H
# define H_STARTUP_H

#include "21sh.h"
#include <dirent.h>

t_environment_node	*parse_environment(char **env);
t_arguments			*parse_arguments(int ac, char **av);

void				load_config_file(t_registry *reg);
unsigned int		init_workspace(t_registry *reg);

void	init_debug_logger(void);

#endif
