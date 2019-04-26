/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reso.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 09:10:39 by nrechati          #+#    #+#             */
/*   Updated: 2019/04/24 17:36:02 by nrechati         ###   ########.fr       */
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
int init_job6(t_job *job);
t_list *test6(void);
int init_job7(t_job *job);
t_list *test7(void);
int init_job8(t_job *job);
t_list *test8(void);
int init_job9(t_job *job);
t_list *test9(void);
int init_job_a(t_job *job);
t_list *test_a(void);
int init_job_b(t_job *job);
t_list *test_b(void);
int init_job_c(t_job *job);
t_list *test_c(void);
int init_job_d(t_job *job);
t_list *test_d(void);
int init_job_e(t_job *job);
t_list *test_e(void);
int init_job_f(t_job *job);
t_list *test_f(void);
int init_job_g(t_job *job);
t_list *test_g(void);
int init_job_h(t_job *job);
t_list *test_h(void);
int init_job_i(t_job *job);
t_list *test_i(void);
//	int init_job_j(t_job *job);
//	t_list *test_j(void);
//	int init_job_k(t_job *job);
//	t_list *test_k(void);
int init_job_l(t_job *job);
t_list *test_l(void);
int init_job_m(t_job *job);
t_list *test_m(void);
int init_job_n(t_job *job);
t_list *test_n(void);
int init_job_o(t_job *job);
t_list *test_o(void);
int init_job_p(t_job *job);
t_list *test_p(void);

// ">" test
#define EXEC_TEST_1 "ls -l > testfile"		/*	OK	*/
#define EXEC_TEST_2 "ls 404 2>errfile"		/*	OK	*/
#define EXEC_TEST_3 "ls 404 2>&-"			/*	OK	*/
#define EXEC_TEST_4 "ls 404 2>&1"			/*	OK	*/
#define EXEC_TEST_5 "ls -l . 404 1>&2"		/*	OK	*/

// ">>" test
#define EXEC_TEST_6 "ls -l >> testfile"		/*	OK	*/
#define EXEC_TEST_7 "ls 404 2>>errfile"		/*	OK	*/
#define EXEC_TEST_P1 "ls 404 2>>&-"			/* Parse Error */
#define EXEC_TEST_P2 "ls 404 2>>&1"			/* Parse Error */
#define EXEC_TEST_P3 "ls -l 1>>&2"			/* Parse Error */

// "<" test									/* Parser : IONBR1<&IONBR2 => IONBR2>&IONBR1 */
#define EXEC_TEST_8 "cat -e < file1"		/*	OK	*/
#define EXEC_TEST_9 "cat -e <&2"			/*	OK	*/
#define EXEC_TEST_A "cat -e <&-"			/*	OK	*/
#define EXEC_TEST_B "cat -e 1<&-"			/*	OK	*/
#define EXEC_TEST_C "cat -e 2<&-" 			/*	OK	*/
#define EXEC_TEST_D "cat -e 0<&-"			/*	OK	*/
#define EXEC_TEST_E "ls -l <&-"				/*	OK	*/
#define EXEC_TEST_F "ls -l <errfile"		/*	OK	*/
#define EXEC_TEST_G "ls 404 2<&-"			/*	OK	*/

// "|" test
#define EXEC_TEST_H "ls -l | cat -e"		/*	OK	*/
#define EXEC_TEST_I "cat -e | ls -l"
#define EXEC_TEST_J "ls -l | echo \"slt\""
#define EXEC_TEST_K "cd / | ls -l"

// Combined test
#define EXEC_TEST_L "ls -l 404 2>&1 | cat -e"
#define EXEC_TEST_M "ls -l | cat -e <&1"
#define EXEC_TEST_N "ls -l | cat -e <&-"
#define EXEC_TEST_O "ls -l | cat -e  | wc -l"
#define EXEC_TEST_P "ls -l > testfile | cat -e"

#endif
