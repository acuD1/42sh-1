/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 09:10:39 by nrechati          #+#    #+#             */
/*   Updated: 2019/04/17 13:20:43 by nrechati         ###   ########.fr       */
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

// Basic test
#define EXEC_TEST_1 "ls -la -h /home"
#define EXEC_TEST_2 "mkdir canyouseeme ; ls -lh"
#define EXEC_TEST_3 "cat -e"

#define EXEC_TEST_4 "echo \"Echo was here\" > echofile"
#define EXEC_TEST_5 "echo \"Not anymore\" > echofile"

// '>' tests
#define EXEC_TEST_6 "ls -l > tempfile"
#define EXEC_TEST_7 "ls -lai > tempfile"
#define EXEC_TEST_8 "ls -la 404 2> errorfile"

#define EXEC_TEST_9 "ls -la Makefile 404 > tempfile 2>&1"
#define EXEC_TEST_A "ls -la Makefile 404 2>&1 > tempfile"

// '>>' tests
#define EXEC_TEST_B "ls -lhi >> tempfile"
#define EXEC_TEST_C "ls -lhi >> newfile"
#define EXEC_TEST_D "ls -lhi 404 2>> errorfile"

// '<' tests
#define EXEC_TEST_E "cat < fichier"
#define EXEC_TEST_F "cat < fichier fichier2 fichier3"
#define EXEC_TEST_G "cat < 404"


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
