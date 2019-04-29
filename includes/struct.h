/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 15:25:34 by ffoissey          #+#    #+#             */
/*   Updated: 2019/04/27 16:35:01 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

/*
*****************************************************
********************** BUILTIN **********************
*****************************************************
*/

typedef uint8_t t_option;
typedef t_option (*t_get_option)(char *s, t_option option);

enum e_state_option
{
	E_START_OPTION,
	E_OPTION,
	E_END_OPTION,
	E_NO_OPTION
};

/*
*****************************************************
*********************** LEXER ***********************
*****************************************************
*/

typedef struct s_lexer t_lexer;
typedef  void (*t_lexing)(t_lexer *);
typedef enum e_type t_type;

enum	e_lexer_state
{
	START,
	LETTER,
	IO_NUMBER,
	SIGN,
	DSIGN,
	GREATER,
	LESSER,
	GREATAND,
	LESSAND,
	TILDE,
	EXP,
	BSL,
	SQTE,
	DQTE,
	BQTE,
	OUT,
	END,
	FINISH
};

enum	e_type
{
	E_EXP,
	E_BACKSLASH,
	E_QUOTE,
	E_DB_QUOTE,
	E_PIPE,
	E_PARENT_OPEN,
	E_PARENT_CLOSE,
	E_GREAT,
	E_LESS,
	E_SEMICOLON,
	E_BACKQUOTE,
	E_AND,
	E_TILDE,
	E_HOOK_OPEN,
	E_HOOK_CLOSE,
	E_BRACKET_OPEN,
	E_BRACKET_CLOSE,
	E_STAR,
	E_INTERROGATION,
	E_EXCLAMATION,
	E_HASH,
	E_PERCENT,
	E_NEWLINE,
	E_DAND,
	E_OR,
	E_DSEMI,
	E_DLESS,
	E_DGREAT,
	E_LESSAND,
	E_GREATAND,
	E_LESSGREAT,
	E_DLESSDASH,
	E_CLOBBER,
	E_DEQ,
	E_NOTEQ,
	E_CASE,
	E_DO,
	E_DONE,
	E_ELIF,
	E_ELSE,
	E_ESAC,
	E_FI,
	E_FOR,
	E_IF,
	E_IN,
	E_THEN,
	E_UNTIL,
	E_WHILE,
	E_IO_NUMBER,
	E_STRING,
	E_QSTRING,
	E_ASSIGN,
	E_END,
	E_DEFAULT,
	E_ERROR,
};

enum	e_quote
{
	QUOTE_OFF,
	QUOTE_ON,
	QUOTE_INT,
	QUOTE_SP,
	QUOTE_SP_INT,
};

typedef struct	s_token
{
	enum e_type	type;
	char		*data;
}				t_token;

struct	s_lexer
{
	char				*input;
	char				buffer[BUFFER];
	t_lexing			process[STATENBR];
	enum e_type			duplicate[TOKEN_WITH_DATA];
	enum e_type			special_signs[SPECIAL_SIGNS];
	t_list				*tokens;
	enum e_lexer_state	state;
	enum e_quote		quote;
	enum e_type			last_lexer;
};

/*
*****************************************************
********************** PARSER ***********************
*****************************************************
*/

typedef struct s_graph		t_graph;
typedef struct s_parser		t_parser;
typedef void (*t_parsing)(t_parser *);

enum	e_parser_state
{
	P_START,
	P_END,
	P_STOP,
	P_ERROR,
	P_STRING,
	P_QUOTE,
	P_STRING_FLUSH,
	P_SEPARATOR,
	P_REDIRECT,
	P_FILENAME,
	P_IO,
	P_PIPE,
	P_REDIRECT_FLUSH,
	P_HEREDOC,
};

enum	e_event
{
	NO_EVENT,
	START_GRAPH,
	END_GRAPH,
	RECALL,
	BACK,
	ERROR_GRAPH
};

typedef struct			s_filedesc
{
	int32_t				in;
	int32_t				out;
	int32_t				err;
}						t_filedesc;

typedef struct	s_process
{
	t_filedesc	fd;
	char		**av;
	char		**env;
	uint8_t		completed;
	uint8_t		stopped;
	int			status;
	pid_t		pid;
}				t_process;

typedef struct	s_job
{
	char			*command; /* just for debug */
	t_list			*process_list;
	pid_t			pgid;
	struct termios	*term_modes;
	t_filedesc		fd;
}				t_job;

struct s_parser
{
	t_process			process;
	t_job				job;
	t_parsing			parsing[PARSE_STATES][NB_OF_TOKENS];
	t_list				*token_list;
	t_list				*env;
	t_list				*tmp_env;
	t_list				*job_list;
	t_stack				stack;
	t_token				token;
	int					oflags;
	int					*fd;
	int					valid;
	enum e_parser_state	last_state;
	enum e_parser_state	state;
};

struct s_graph
{
	enum e_type		*good_type;
	int				nb_of_good_type;
};

/*
*****************************************************
********************** HISTORY **********************
*****************************************************
*/

typedef struct			s_history
{
	char				*command;
	struct s_history 	*next;
	struct s_history 	*prev;
}						t_history;

/*
*****************************************************
******** -------------- COMMON -------------- *******
*****************************************************
*/

typedef struct s_opt
{
	int		help;	//TODO: Implement this
	int		version;	//TODO: Implement this
	int		debug;	//TODO: Change implementation
	int		command;	//TODO: Implement this
	char	*command_str;  //TODO: Implement for -c
//	int		norc; // TODO: Mute this for 21sh
//	int		rcfile;//TODO: Mute this for 21sh
//	char	*rc_path; //TODO: Mute this for 21sh // rcfile
}				t_opt;

typedef struct	s_node
{
	char *var;
	char *data;
}				t_node;


/*
*****************************************************
**************** INTERFACE_FUNCTIONS ****************
*****************************************************
*/

enum action_keys {
	AK_ARROW_RIGHT,
	AK_ARROW_LEFT,
	AK_ARROW_UP,
	AK_ARROW_DOWN,
	AK_HOME,
	AK_END,
	AK_BACKSPACE,
	AK_DELETE,
	AK_CTRL_A,
	AK_CTRL_D,
	AK_CTRL_E,
	AK_CTRL_L,
	AK_CTRL_X,
	AK_CTRL_B,
	AK_CTRL_P,
	AK_CTRL_LB,
	AK_CTRL_RB,
	AK_CTRL_F,
	AK_CTRL_R,
	AK_CTRL_LEFT,
	AK_CTRL_RIGHT,
	AK_TABULATION,
	AK_CTRL_DOWN,
	AK_CTRL_UP,
};

typedef struct				s_termcaps
{
	char					*clear;
	char					*cs_down;
	char					*cs_right;
	char					*cs_left;
	char					*cs_up;
}							t_termcaps;

typedef struct				s_cursor
 {
	uint32_t				index;
	uint32_t				x;
	uint32_t				y;
}							t_cursor;

typedef struct				s_window
{
	uint32_t				rows;
	uint32_t				cols;
	uint32_t				max_chars;
}							t_window;

typedef struct				s_registry t_registry;

typedef struct				s_interface
{
	struct termios			*term_mode;
	struct termios			*orig_mode;
	t_vector				*line;
	t_vector				*clip;
	t_cursor				cursor;
	t_window				window;
	t_termcaps				termcaps;
	t_history				*history_head;
	t_history				*hist_ptr;
	char					*current_line;
	char					*state;
	unsigned long			ak_masks[AK_AMOUNT];
	int8_t					(*tc_call[AK_AMOUNT])(struct s_registry *shell);
}							t_interface;



struct				s_registry
{
	t_opt					option;
	t_list					*env;
	t_list					*intern;
	t_hash					bin_hashmap;
	t_hash					blt_hashmap;
	struct s_interface		interface;
	//TODO: move t_job head here for exit and global
	//t_list				*job_list;
	t_graph					graph[NB_OF_TOKENS];
	t_parser				parser;
};

typedef int 		(*t_builtin)(t_registry *, char **);

extern t_registry	*g_shell;
/*
*****************************************************
********************** RESOLVE **********************
*****************************************************
*/

extern t_list	*g_job_head;

#endif

