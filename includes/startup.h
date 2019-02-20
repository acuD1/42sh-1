/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   startup.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 14:36:38 by skuppers          #+#    #+#             */
/*   Updated: 2019/02/20 10:28:19 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STARTUP_H
# define STARTUP_H

#include "21sh.h"

t_environment_node	*parse_environment(char **env);
unsigned int		parse_arguments(int ac, char **av);

void	load_config_file(void);
void	init_workspace(void);

void	init_debug_logger(void);

#endif
