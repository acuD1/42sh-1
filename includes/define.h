/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 14:17:21 by ffoissey          #+#    #+#             */
/*   Updated: 2019/04/30 21:11:21 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_H
# define DEFINE_H

/*
*****************************************************
******** -------------- COMMON -------------- *******
*****************************************************
*/

# define SUCCESS					0
# define FAILURE					-1
# define FALSE						0
# define TRUE						1
# define SH21_USAGE_1				"Usage: 21sh [long option] [-dhv] "
# define SH21_USAGE_2				"[--rcfile PATH] [-c CMD]\n"
# define SH21_USAGE_LONG_OPTION		"\n\t--help\n\t--norc\n\t"
# define SH21_USAGE_LONG_OPTION_2	"--version\n\t--debug\n"
# define NO_OPT						0x000
# define HELP_OPT					0x001
# define COMMAND_OPT				0x002
# define DEBUG_OPT					0x004
# define VERSION_OPT				0x008
# define NORC_OPT					0x010
# define RCFILE_OPT					0x020

/*
*****************************************************
********************** BUILTIN **********************
*****************************************************
*/

# define A_OPT						0x001
# define F_OPT						0x002
# define I_OPT						0x004
# define L_OPT						0x008
# define N_OPT						0x010
# define P_OPT						0x020
# define T_OPT						0x040
# define P_LOW_OPT					0x080
# define ERROR_OPT					0x800
# define CD_USAGE 					"cd: usage: cd [-L|-P] [dir]\n"
# define CD_ERROR_OLDPWD_NOTSET		"21sh: cd: OLDPWD not set\n"
# define ENV_USAGE_1 				"env: usage: env [-i] [name=value]... "
# define ENV_USAGE_2 				"[utility [argument]...]\n"
# define SETENV_USAGE 				"setenv: usage: setenv [name [value]]\n"
# define UNSETENV_USAGE 			"unsetenv: usage: unsetenv name\n"
# define TYPE_USAGE 				"type: usage: type [-afptP] name [name ...]\n"
# define EXPORT_USAGE 				"type: usage: export name[=value] ...\n"
# define UNSET_USAGE 				"type: usage: unset name\n"

/*
*****************************************************
********************* INTERNALS *********************
*****************************************************
*/

# define IFS_CHAR					10
# define READ_SIZE					8
# define CLIPBOARD_SZ				32
# define INT_TERM					"TERM"
# define INT_TERM_DFLT_VALUE		"xterm-256color"
# define INT_DBG_FD					"DEBUG_FD"
# define INT_DBG_FILE				".42sh.log"
# define INT_ROWS					"ROWS"
# define INT_COLS					"COLS"
# define INT_PS1					"PS1"
# define INT_PS2					"PS2"
# define INT_PS3					"PS3"
# define INT_PS4					"PS4"
# define INT_PS5					"PS5"
# define INT_ESCAPE_SEQ				"ESC"
# define INT_PS1_VALUE				"[21sh] -> "
# define INT_PS2_VALUE				"quote> "
# define INT_PS3_VALUE				"script> "
# define INT_PS4_VALUE				"heredoc> "
# define INT_ESCAPE_SEQ_VALUE		"\\"
# define INT_MAGIC_NUMBER			"4242"

/*
*****************************************************
*********************** LEXER ***********************
*****************************************************
*/

# define STATENBR					19
# define TOKEN_WITH_DATA			12
# define NB_OF_TOKENS				59
# define BUFFER						1024
# define SINGLE_SIGNS				23
# define SPECIAL_SIGNS				15
# define SIGNS 						(SPECIAL_SIGNS + SINGLE_SIGNS)
# define ALLCHAR					"$\\\'\"|()><;`&~{}[]*?!#%N"
# define SIGN_DETECT				" \t<>|;\'\"$&~\\"
# define LETTER_TO_QUOTE			"\"\'$"
# define LETTER_INTERUPT			" \t<>|;&\\"
# define TILDE_INTERUPT				" /$"
# define QSP_INT					" \"\'"
/*
** 42sh
** # define LETTER_INTERUPT			" \t<>|;\'\"`()$&!?{}[]*%\\"
** # define SIGN_DETECT				" \t<>|;\'\"`()$&!?{}[]*%\\="
**/
# define QUOTE_INTERUPT				"\\\"`$"
# define EXP_INTERUPT				" \t\'\"`"
# define DOUBLE_SIGN				"&|;=!"
# define CASE						"case"
# define DO							"do"
# define DONE						"done"
# define ELIF						"elif"
# define ELSE						"else"
# define ESAC						"esac"
# define FI							"fi"
# define FOR						"for"
# define IF							"if"
# define IN							"in"
# define THEN						"then"
# define UNTIL						"until"
# define WHILE						"while"

/*
*****************************************************
********************** PARSER ***********************
*****************************************************
*/

# define PARSE_STATES				20
# define STARTING					14
# define STRING_TOKENS				16
# define BACKSLASH 					E_BACKSLASH
# define STRING_WORD 				E_STRING, E_EXP, E_QUOTE, E_DB_QUOTE
# define IO							E_IO_NUMBER
# define PIPELINE					E_PIPE
# define BASE_REDIRECT				E_GREAT, E_LESS, E_DLESS, E_DGREAT
# define AND_REDIRECT				E_GREATAND, E_LESSAND
# define END_CMD					E_SEMICOLON, E_END
# define REDIRECT					AND_REDIRECT, BASE_REDIRECT
# define WORD						STRING_WORD, BACKSLASH
# define ALL						WORD, BASE_REDIRECT, IO
# define ALL_END					ALL, END_CMD
# define E_START					E_DEFAULT

/*
*****************************************************
**************** INTERFACE_FUNCTIONS ****************
*****************************************************
*/

# define AK_AMOUNT					24
# define AK_ARROW_UP_MASK			0x1b5b410000000000
# define AK_ARROW_DOWN_MASK 		0x1b5b420000000000
# define AK_ARROW_RIGHT_MASK		0x1b5b430000000000
# define AK_ARROW_LEFT_MASK 		0x1b5b440000000000
# define AK_HOME_MASK 				0x1b5b480000000000
# define AK_END_MASK 				0x1b5b460000000000
# define AK_CTRL_A_MASK 			0x0100000000000000
# define AK_CTRL_E_MASK		   		0x0500000000000000
# define AK_DELETE_MASK		   		0x1b5b337e00000000
# define AK_BACKSPACE_MASK		 	0x7f00000000000000
# define AK_CTRL_D_MASK 			0x0400000000000000
# define AK_CTRL_L_MASK				0x0c00000000000000
# define AK_CTRL_X_MASK				0x1800000000000000
# define AK_CTRL_B_MASK				0x0200000000000000
# define AK_CTRL_P_MASK				0x1000000000000000
# define AK_CTRL_LB_MASK			0x1b00000000000000
# define AK_CTRL_RB_MASK			0x1d00000000000000
# define AK_CTRL_F_MASK				0x0600000000000000
# define AK_CTRL_R_MASK				0x1200000000000000
# define AK_CTRL_UP_MASK			0x1b5b313b35410000
# define AK_CTRL_DOWN_MASK			0x1b5b313b35420000
# define AK_CTRL_RIGHT_MASK			0x1b5b313b35430000
# define AK_CTRL_LEFT_MASK			0x1b5b313b35440000
# define AK_TAB_MASK				0x0900000000000000

/*
*****************************************************
************************ LOG ************************
*****************************************************
*/

# define LOG_OK						"[OK]"
# define LOG_INFO 					"[INFO]"
# define LOG_WARNING				"[WARNING]"
# define LOG_ERROR					"[ERROR]"
# define LOG_CRITICAL				"[CRITICAL]"

/*
*****************************************************
********************** HISTORY **********************
*****************************************************
*/

# define DEFAULT_HISTORY_FILENAME	".sh_history"

/*
*****************************************************
*********************** UNIT ************************
*****************************************************
*/

# define BLUE						"39"
# define T_CHMOD					766

#endif
