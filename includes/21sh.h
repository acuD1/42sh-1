/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   21sh.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 13:17:19 by nrechati          #+#    #+#             */
/*   Updated: 2019/04/23 22:21:22 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH21_H
# define SH21_H
# include <stdlib.h>
# include "registry.h"
# include "internals.h"
# include "line_edit.h"

# define USAGE "USAGE ./21sh [-vdh][--help][--norc][--rcfile]PATH[-c]CMD\n"

typedef int 		(*t_builtin)(t_registry *);

typedef struct	t_variable
{
	char *name;
	char *data;
}				t_variable;

void			shell_invoke_interactive(t_registry *shell);

int				add_internal(t_registry *shell, char *name, char *data);
int				add_internal_nbr(t_registry *shell, char *name, int data);
char			*get_intern_var(t_registry  *shell, char *name);

int				hash_blt(t_registry *shell);
int				exit_blt(t_registry *shell);

int				launch_sh(char **av, char **env, t_registry *registry);
int				parse_arg(int index, char **av, t_opt *option);
int				fill_opt(int index, char **av, t_opt *option);
void			print_lst(t_list **alst);
int				s_create_node(t_list **alst, char *name, char *data);
int				change_node(t_list **alst, char *name, char *data);
char			*get_data(t_list *lst, char *name);
void			clear_node(void **data);
int				free_anode(t_list *ptr);
int				del_node(t_list *ptr, char *name);
int				free_node(t_list **alst, char *name);
int				free_lst(t_list **alst);
char			*variable_to_str(void *data);

#endif
