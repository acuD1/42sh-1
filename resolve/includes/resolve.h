/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 09:10:39 by nrechati          #+#    #+#             */
/*   Updated: 2019/04/17 13:06:38 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESOLVE_H
# define RESOLVE_H
# include <stdlib.h>

typedef struct 		s_instr
{
	int				ac;
	char			**av;
	char			**env;
	int				fd_in;
	int				fd_out;
	int				fd_err;
	gid_t			gid;
}					t_instr;

			/*		Test bench 		*/
int		add_to_test(t_list **test, void *fct);
int		new_cmd(t_list **alst, char **env, int (*init)(t_instr *, char **));
int		test_to_bench(t_hash *hashmap, t_list **stack, char **env, char *test);
int 	fill_test_bank(t_hash *hashmap);
int		print_test_stack(t_list **stack, char *test);

			/*		Test 1 : ls -l | cat -e */
t_list	*test1(void);
int		test1_ls(t_instr *cmd, char **env);
int		test1_cat(t_instr *cmd, char **env);

#endif
