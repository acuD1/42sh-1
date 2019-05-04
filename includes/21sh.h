/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   21sh.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 13:17:19 by nrechati          #+#    #+#             */
/*   Updated: 2019/05/04 15:35:46 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH21_H
# define SH21_H

# include "struct.h"

/*
*****************************************************
******************** INIT / EXIT ********************
*****************************************************
*/
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

char	        *read_input(const int fd);
void			launch_interface(t_registry *shell);
int8_t		    execution_pipeline(t_registry *shell, t_list *token_list);
void			get_prompt_ps1(t_registry *shell);


/*
*****************************************************
*********************** VAR *************************
*****************************************************
*/

char			*get_env_var(t_registry  *shell,  char *name);
char			*get_intern_var(t_registry  *shell,  char *name);
int8_t			add_env(t_registry *shell,  char *name,  char *data);
int8_t			add_internal(t_registry *shell,  char *name,
					 char *data);
int8_t			add_internal_nbr(t_registry *shell,  char *name,
					 int data);

/*
*****************************************************
*********************** LIST ************************
*****************************************************
*/

void			print_lst(t_list **alst);
int8_t			f_create_node(t_list **alst, const char *str);
int8_t			s_create_node(t_list **alst, const char *var, const char *data);
int8_t			change_node(t_list **alst, const char *var, char *data);
char			*get_data(t_list *lst, char *var);
void			print_process(t_list *node);
char			*variable_to_str(void *data);
int				find_variable(void *data, void *to_find);

/*
*********************** FREE
*/

void			clear_node(void **data);
int8_t			free_node(t_list **alst, char *var);
int8_t			free_lst(t_list **alst);
void			delete_variable(void *data);
void			delete_parser(t_parser *parse);
void			delete_process(void *data);
void			delete_job(void *data);
void			free_token_list(t_list *token_list);
void			free_one_node_token(t_list **token_lst);

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

char	       	*ft_strjoinfree(char *s1, const char *s2, const short todel);

#endif
