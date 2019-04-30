/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 15:25:34 by ffoissey          #+#    #+#             */
/*   Updated: 2019/04/30 21:11:46 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H
# include "define.h"
# include "libft.h"
# include "enum.h"

/*
*****************************************************
********************** BUILTIN **********************
*****************************************************
*/

typedef uint16_t		t_option;
typedef t_option		(*t_get_option)(char *s, t_option option);


/*
*****************************************************
*********************** LEXER ***********************
*****************************************************
*/

typedef struct s_lexer	t_lexer;
typedef void 			(*t_lexing)(t_lexer *);
typedef enum e_type		t_type;

typedef struct			s_token
{
	enum e_type			type;
	char				*data;
}						t_token;

struct					s_lexer
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

typedef struct s_graph	t_graph;
typedef struct s_parser	t_parser;
typedef void			(*t_parsing)(t_parser *);
typedef t_parsing		t_pstate[PARSE_STATES][NB_OF_TOKENS];

typedef struct			s_filedesc
{
	int32_t				in;
	int32_t				out;
	int32_t				err;
}						t_filedesc;

typedef struct			s_process
{
	t_filedesc			fd;
	char				**av;
	char				**env;
	uint8_t				completed;
	uint8_t				stopped;
	int					status;
	pid_t				pid;
}						t_process;

typedef struct			s_job
{
	char				*command; /* just for debug */
	t_list				*process_list;
	pid_t				pgid;
	struct termios		*term_modes;
	t_filedesc			fd;
}						t_job;

struct					s_parser
{
	t_process			process;
	t_job				job;
	t_list				*token_list;
	t_list				*env;
	t_list				*tmp_env;
	t_list				*job_list;
	t_stack				stack;
	t_token				token;
	int					oflags;
	int					valid;
	enum e_parser_state	last_state;
	enum e_parser_state	state;
};

struct					s_graph
{
	enum e_type			*good_type;
	int					nb_of_good_type;
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
**************** INTERFACE_FUNCTIONS ****************
*****************************************************
*/

typedef struct			s_registry t_registry;

typedef struct			s_termcaps
{
	char				*clear;
	char				*cs_down;
	char				*cs_right;
	char				*cs_left;
	char				*cs_up;
}						t_termcaps;

typedef struct			s_cursor
 {
	uint32_t			index;
	uint32_t			x;
	uint32_t			y;
}						t_cursor;

typedef struct			s_window
{
	uint32_t			rows;
	uint32_t			cols;
	uint32_t			max_chars;
}						t_window;

typedef struct			s_interface
{
	struct termios		*term_mode;
	struct termios		*orig_mode;
	t_vector			*line;
	t_vector			*clip;
	t_cursor			cursor;
	t_window			window;
	t_termcaps			termcaps;
	t_history			*history_head;
	t_history			*hist_ptr;
	char				*current_line;
	char				*state;
	unsigned long		ak_masks[AK_AMOUNT];
	int8_t				(*tc_call[AK_AMOUNT])(struct s_registry *shell);
}						t_interface;

/*
*****************************************************
********************** COMMON ***********************
*****************************************************
*/

typedef struct 			s_opt
{
	t_option			option;
	char				*command_str;
//	char				*rc_path;
}						t_opt;

typedef struct			s_variable
{
	char				*name;
	char				*data;
}						t_variable;

struct					s_registry
{
	uint8_t				is_interactive;
	t_opt				option;
	t_list				*env;
	t_list				*intern;
	t_hash				bin_hashmap;
	t_hash				blt_hashmap;
	t_graph				graph[NB_OF_TOKENS];
	t_pstate			parsing;
	t_list				*current_job;
	struct s_interface	interface;
};

typedef int 			(*t_builtin)(t_registry *, char **);

extern t_registry	*g_shell;

/*
*****************************************************
********************** RESOLVE **********************
*****************************************************
*/

extern t_list		*g_job_head;

#endif

