/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reso.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 09:10:39 by nrechati          #+#    #+#             */
/*   Updated: 2019/04/23 17:55:48 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESOLVE_H
# define RESOLVE_H
# include <stdlib.h>
# include "21sh.h"

			/*		Test bench 		*/
int		add_to_test(t_list **test, void *fct);
int		new_cmd(t_list **alst, char **env, int (*init)(t_process *, char **));
int		test_to_bench(t_hash *hashmap, t_list **stack, char **env, char *test);
int 	fill_test_bank(t_hash *hashmap);
int		print_test_joblst(t_list **stack, char *test);
char	*get_line(char	*test);
int		setup_job(t_job *job, char *test);

			/*		Tests */
int init_job1(t_job *job);
t_list *test1(void);
int init_job2(t_job *job);
t_list *test2(void);
int init_job3(t_job *job);
t_list *test3(void);
int init_job4(t_job *job);
t_list *test4(void);
int init_job5(t_job *job);
t_list *test5(void);

// ">" test
#define EXEC_TEST_1 "ls -l > testfile"
#define EXEC_TEST_2 "ls 404 2>errfile"
#define EXEC_TEST_3 "ls 404 2>&-"
#define EXEC_TEST_4 "ls 404 2>&1"
#define EXEC_TEST_5 "ls -l 1>&2"

// ">>" test
#define EXEC_TEST_6 "ls -l >> testfile"
#define EXEC_TEST_7 "ls 404 2>>errfile"
#define EXEC_TEST_8 "ls 404 2>>&-"
#define EXEC_TEST_9 "ls 404 2>>&1"
#define EXEC_TEST_A "ls -l 1>>&2"

// "<" test
#define EXEC_TEST_B "cat -e < file1"
#define EXEC_TEST_C "cat -e <&2"
#define EXEC_TEST_D "cat -e <&-"
#define EXEC_TEST_E "cat -e 0<&-"

#endif
