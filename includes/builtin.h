/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 16:35:32 by ffoissey          #+#    #+#             */
/*   Updated: 2019/04/30 14:24:53 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "21sh.h"
# include <pwd.h>
# include <limits.h>

t_option	set_options(char ***av, t_get_option get_option);

/*
*****************************************************
******************* PWD BUILT-IN ********************
*****************************************************
*/

int8_t		pwd_blt(t_registry *shell, char **av);
t_option	get_option_pwd(char *s, t_option option);
char		*get_pwd(t_registry *shell, t_option option);

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
******************* ENV BUILT-IN ********************
*****************************************************
*/

int8_t				env_blt(t_registry *shell, char **av);
t_option			get_option_env(char *s, t_option option);

/*
*****************************************************
****************** SETENV BUILT-IN ******************
*****************************************************
*/

int8_t				setenv_blt(t_registry *shell, char **av);

/*
*****************************************************
***************** UNSETENV BUILT-IN *****************
*****************************************************
*/

int8_t				unsetenv_blt(t_registry *shell, char **av);

/*
*****************************************************
****************** INTERN BUILT-IN ******************
*****************************************************
*/

int8_t				intern_blt(t_registry *shell, char **av);

/*
*****************************************************
******************* EXIT BUILT-IN *******************
*****************************************************
*/

int8_t				exit_blt(t_registry *reg, char **av);

/*
*****************************************************
******************* TYPE BUILT-IN *******************
*****************************************************
*/

int8_t				type_blt(t_registry *shell, char **av);
t_option			get_option_type(char *s, t_option option);

/*
*****************************************************
******************* HASH BUILT-IN *******************
*****************************************************
*/

int8_t				hash_blt(t_registry *reg, char **av);

/*
*****************************************************
****************** EXPORT BUILT-IN ******************
*****************************************************
*/

int8_t				export_blt(t_registry *shell, char **av);
t_option			get_export_export(char *s, t_option option);

/*
*****************************************************
******************* SET BUILT-IN ********************
*****************************************************
*/

int8_t				set_blt(t_registry *reg, char **av);

/*
*****************************************************
****************** UNSET BUILT-IN *******************
*****************************************************
*/

int8_t				unset_blt(t_registry *reg, char **av);

#endif
