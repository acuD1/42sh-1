/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh21.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 13:17:19 by nrechati          #+#    #+#             */
/*   Updated: 2019/04/03 16:35:34 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH21_H
# define SH21_H
# include <stdlib.h>
# include "libft.h"
# include "internals.h"

typedef struct s_opt
{
	int		h;
	int		v;
	int		d;
	int		c;
	int		norc;
	int		rcfile;
	char	*cmd;
	char	*path;
}				t_opt;

typedef struct	s_node
{
	char *var;
	char *data;
}				t_node;




typedef struct		s_registry
{
	t_opt			option;
	t_list			*env;
	t_list			*intern;
}					t_registry;



void			shell_invoke_interactive(t_registry *shell_registry);

int				add_internal(t_registry *sh_reg, char *name, char *data);
int				add_internal_nbr(t_registry *reg, char *name, int data);
char			*get_intern_var(t_registry  *sh_reg, char *name);


int				launch_sh(int ac, char **av, char **env, t_registry *registry);
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

#endif
