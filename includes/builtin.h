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
# include "21sh.h"
# include <pwd.h>
# include <unistd.h>

# include <limits.h>
# include <sys/stat.h>
# include <sys/types.h>

# define SUCCESS			0
# define FAILURE			-1

# define N_OPT		0x0000000000000001
# define L_OPT		0x0000000000000002
# define P_OPT		0x0000000000000004
# define I_OPT		0x0000000000000008
# define ERROR_OPT	0x1000000000000000

# define CD_USAGE "cd: usage: cd [-L|-P] [dir]\n"
# define ENV_USAGE "env: usage: env [-i] [name=value]... [utility [argument]...]\n"
# define CD_ERROR_OLDPWD_NOTSET "21sh: cd: OLDPWD not set\n"

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

/*
*****************************************************
******************* ECHO BUILT-IN *******************
*****************************************************
*/

int8_t		echo_blt(t_registry *shell, char **av);

/*
*****************************************************
******************** CD BUILT-IN ********************
*****************************************************
*/

int8_t		cd_blt(t_registry *shell, char **av);
t_option	get_option_cd(char *s, t_option option);
char		*concat_pwd_with_curpath(t_registry *shell, char **path);
char		*get_home_path(void);
char		*is_cdpath_env(t_registry *shell, char *to_find);
char		*get_relative_path(char **curpath);
char		*make_curpath_simple(char *curpath);

/*
*****************************************************
******************* ENV  BUILT-IN *******************
*****************************************************
*/

int8_t				env_blt(t_registry *shell, char **av);
t_option			get_option_env(char *s, t_option option);

#endif
