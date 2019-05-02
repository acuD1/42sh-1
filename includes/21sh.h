/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   21sh.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 13:17:19 by nrechati          #+#    #+#             */
/*   Updated: 2019/05/02 03:12:36 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH21_H
# define SH21_H

# include "libft.h"
# include "define.h"
# include "struct.h"
# include "interface_functions.h"

/////////////// LINUX
# include <signal.h>
# include <sys/wait.h>
/////////////////////

/*
*****************************************************
******************** INIT / EXIT ********************
*****************************************************
*/
void			get_prompt_ps1(t_registry *shell);

void			define_default_signals(t_registry *shell);
void			free_registry(t_registry *shell);

int8_t			init_shell(t_registry *shell);
int8_t			set_environment( t_registry *shell, char **av, char **env);
void			init_lexinfo(t_registry *shell);
int8_t			shell_usage(void);
void			shell_exit_routine(t_registry *shell);

/*
*****************************************************
****************** READ / INTERFACE *****************
*****************************************************
*/

char	        *read_input(int fd);
void			launch_interface(t_registry *shell);
int8_t		    execution_pipeline(t_registry *shell, t_list *token_list);


/*
*****************************************************
*********************** VAR *************************
*****************************************************
*/

int				add_env(t_registry *sh_reg, char *name, char *data);
int				add_internal(t_registry *sh_reg, char *name, char *data);
int				add_internal_nbr(t_registry *reg, char *name, int data);
char			*get_env_var(t_registry  *sh_reg, char *name);
char			*get_intern_var(t_registry  *sh_reg, char *name);

/*
*****************************************************
*********************** LIST ************************
*****************************************************
*/

void			print_lst(t_list **alst);
int8_t			f_create_node(t_list **alst, char *str);
int8_t			s_create_node(t_list **alst, char *var, char *data);
int8_t			change_node(t_list **alst, char *var, char *data);
char			*get_data(t_list *lst, char *var);
char			*variable_to_str(void *data);
int				find_variable(void *data, void *to_find);

/*
*********************** FREE
*/

void			clear_node(void **data);
int8_t			free_node(t_list **alst, char *var);
int8_t			free_lst(t_list **alst);
void			delete_parser(t_parser *parse);
void			delete_process(void *data);
void			delete_job(void *data);

/*
*****************************************************
********************* OPTION ************************
*****************************************************
*/

void	        print_opt(t_registry *shell);

/*
*****************************************************
********************** TOOLS ************************
*****************************************************
*/

char	       	*ft_strjoinfree(char *s1, char *s2, short todel);

#endif
