/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   21sh.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 13:17:19 by nrechati          #+#    #+#             */
/*   Updated: 2019/04/27 14:12:34 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH21_H
# define SH21_H
# include <stdlib.h>
# include "libft.h"
# include "internals.h"
# include "lexer.h"
# include "parser.h"

# define SUCCESS			0
# define FAILURE			-1
# define FALSE				0
# define TRUE				1

typedef struct s_opt
{
	int		h;	//TODO: Implement this
	int		v;	//TODO: Implement this
	int		d;	//TODO: Change implementation
	int		c;	//TODO: Implement this
	char	*cmd;  //TODO: Implement for -c
	int		norc; // TODO: Mute this for 21sh
	int		rcfile;//TODO: Mute this for 21sh
	char	*path; //TODO: Mute this for 21sh // rcfile
}				t_opt;

typedef struct	s_node
{
	char *var;
	char *data;
}				t_node;

typedef struct				s_registry
{
	t_opt					option;
	t_list					*env;
	t_list					*intern;
	t_hash					bin_hashmap;
	t_hash					blt_hashmap;
	struct s_interface		*interface;

	//TODO: move t_job head here for exit and global

	t_parser				*parser;
	//t_list				*job_list;
}							t_registry;

# include "line_edit.h"

typedef int 		(*t_builtin)(t_registry *, char **);

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

char		*variable_to_str(void *data);
void		delete_process(void *data);
void		delete_job(void *data);
#endif
