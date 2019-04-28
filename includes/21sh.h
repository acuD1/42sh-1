/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   21sh.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 13:17:19 by nrechati          #+#    #+#             */
/*   Updated: 2019/04/27 16:24:38 by ffoissey         ###   ########.fr       */
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

int				lexer_parser(t_parser *parse, t_graph *graph, char *input);
void			shell_invoke_interactive(t_registry *shell);

int				add_internal(t_registry *sh_reg, char *name, char *data);
int				add_internal_nbr(t_registry *reg, char *name, int data);
int				add_env(t_registry *sh_reg, char *name, char *data);
char			*get_env_var(t_registry  *sh_reg, char *name);
char			*get_intern_var(t_registry  *sh_reg, char *name);

int				launch_sh(char **av, char **env, t_registry *registry);
int				parse_arg(int index, char **av, t_opt *option);
int				fill_opt(int index, char **av, t_opt *option);
void			print_lst(t_list **alst);
int				f_create_node(t_list **alst, char *str);
int				s_create_node(t_list **alst, char *var, char *data);
int				change_node(t_list **alst, char *var, char *data);
int				search_data(t_list **alst, char *var);
char			*get_data(t_list **alst, char *var);
void			clear_node(void **data);
int				free_anode(t_list *ptr);
int				del_node(t_list *ptr, char *var);
int				free_node(t_list **alst, char *var);
int				free_lst(t_list **alst);

char			*variable_to_str(void *data);
void			delete_process(void *data);
void			delete_job(void *data);

#endif
