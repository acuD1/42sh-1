/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 16:35:32 by ffoissey          #+#    #+#             */
/*   Updated: 2019/04/24 18:13:09 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "interface_functions.h"
# include "parser.h"

# define SUCCESS			0
# define FAILURE_OPTION		1

# define N_OPT		0x0000000000000001
# define L_OPT		0x0000000000000002
# define P_OPT		0x0000000000000004
# define ERROR_OPT	0x1000000000000000

# define CD_USAGE "cd: usage: cd [-L|-P] [dir]\n"

typedef unsigned long t_option;
typedef t_option (*t_get_option)(char *s, t_option option);

enum e_state_option
{
	E_START_OPTION,
	E_OPTION,
	E_END_OPTION,
	E_NO_OPTION

};

t_option	set_options(char ***av, t_get_option get_option);

int8_t		echo_blt(t_registry *shell, char **av);

int8_t		cd_blt(t_registry *shell, char **av);
char		*is_cdpath_env(t_registry *shell, char *to_find);
t_option	get_option_cd(char *s, t_option option);


#endif
