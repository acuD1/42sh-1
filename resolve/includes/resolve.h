/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 09:10:39 by nrechati          #+#    #+#             */
/*   Updated: 2019/04/23 13:38:24 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESOLVE_H
# define RESOLVE_H
# include <stdlib.h>
# include "21sh.h"


typedef struct		filedesc_s
{
	int32_t			in;
	int32_t			out;
	int32_t			err;
}					t_filedesc;

typedef struct 		s_process
{
	int				ac;
	char			**av;
	char			**env;
	t_filedesc		fd;
	gid_t			gid;
}					t_process;

typedef struct		job_t
{

	char			*command; /* unused */
	t_list			*f_process;
	pid_t			pgid;
	struct termios	*term_modes;
	t_filedesc		*fd;

}					t_job;

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

			/*		Resolve 		*/
int		resolve_stack(t_list **stack, t_registry *shell);

			/*		Test bench 		*/
int		add_to_test(t_list **test, void *fct);
int		new_cmd(t_list **alst, char **env, int (*init)(t_instr *, char **));
int		test_to_bench(t_hash *hashmap, t_list **stack, char **env, char *test);
int 	fill_test_bank(t_hash *hashmap);
int		print_test_stack(t_list **stack, char *test);
char	*get_line(char	*test);

			/*		Tests */
t_list	*test1(void);
t_list	*test2(void);
t_list	*test3(void);
t_list	*test4(void);
t_list	*test5(void);
t_list	*test6(void);
t_list	*test7(void);
t_list 	*test8(void);
t_list 	*test_a(void);
t_list 	*test_b(void);
t_list 	*test_c(void);
t_list 	*test_d(void);
t_list 	*test_e(void);
t_list 	*test_f(void);
t_list 	*test_g(void);

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

// "simple" pipe test
#define EXEC_TEST_B "cat -e < file1"
#define EXEC_TEST_C "cat -e <&2"
#define EXEC_TEST_D "cat -e <&-"
#define EXEC_TEST_E "cat -e 0<&-"

#endif
