/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 09:10:39 by nrechati          #+#    #+#             */
/*   Updated: 2019/04/19 16:55:16 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESOLVE_H
# define RESOLVE_H
# include <stdlib.h>
# include "21sh.h"

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

// Basic test
#define EXEC_TEST_1 "ls -l -h /Users/nrechati"
#define EXEC_TEST_2 "cat -e"

#define EXEC_TEST_3 "echo \"Echo was here\" > echofile"
#define EXEC_TEST_4 "echo \"Not anymore\" > echofile"

// '>' tests
#define EXEC_TEST_5 "ls -l > tempfile"
#define EXEC_TEST_6 "ls -lai > tempfile"
#define EXEC_TEST_7 "ls -la 404 2> errorfile"

#define EXEC_TEST_8 "ls -la Makefile 404 > tempfile 2>&1"
#define EXEC_TEST_A "ls -la Makefile 404 2>&1 > tempfile"

// '>>' tests
#define EXEC_TEST_B "ls -lhi >> tempfile"
#define EXEC_TEST_C "ls -lhi >> newfile"
#define EXEC_TEST_D "ls -lhi 404 2>> errorfile"

// '<' tests
#define EXEC_TEST_E "cat -e < fichier"
#define EXEC_TEST_F "cat < fichier fichier2 fichier3" /* Gerer via av */
#define EXEC_TEST_G "cat < 404"						  /* Open fail */


// '<<' tests (heredoc)
#define EXEC_TEST_H "cat <<EOF"

// Pipe tests
#define EXEC_TEST_I "ls -l | cat -e"
#define EXEC_TEST_J "cat -e | ls -l"

// Hard tests
#define EXEC_TEST_K "cat <<EOF > fichierEOF"

// OPTIONEL VOIR DOCUMENTATION
// Equivalent a     "ls -lh Makefile 404 >log 2>&1"
#define EXEC_TEST_L "ls -lh Makefile 404 &> log" //redirige fd 1 et 2
#define EXEC_TEST_M "ls -lh Makefile 404 &>> log" //redirige fd 1 et 2
#define EXEC_TEST_N "ls -lh Makefile 404 &| cat -e" //redirige fd 1 et 2
#define EXEC_TEST_O "ls -la > fileX"
#define EXEC_TEST_P "ls -la >| fileX" //voir. NoClobber - Bash

#endif
