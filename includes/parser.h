/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 13:39:31 by cempassi          #+#    #+#             */
/*   Updated: 2019/04/26 16:31:05 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "libft.h"
# include "lexer.h"
# define TRUE 1
# define FALSE 0
# define PARSE_STATES 14

# define STARTING 14
# define STRING_TOKENS 16

# define WORD E_STRING, E_EXP, E_QUOTE, E_DB_QUOTE, E_BACKSLASH
# define IO E_IO_NUMBER
# define PIPELINE E_PIPE
# define BASE_REDIRECT E_GREAT, E_LESS, E_DLESS, E_DGREAT
# define AND_REDIRECT E_GREATAND, E_LESSAND
# define REDIRECT AND_REDIRECT, BASE_REDIRECT
# define END_CMD E_SEMICOLON, E_END
# define ALL WORD, BASE_REDIRECT, IO
# define ALL_END ALL, END_CMD
# define E_START E_DEFAULT

typedef struct s_graph		t_graph;
typedef struct s_parser		t_parser;
typedef void (*t_parsing)(t_parser *);

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

int		lexer_parser(t_parser *parse, char *input);
void	init_parser(t_parser *parse);
void	init_process(t_process *process);
t_list	*parser_state(t_parser *parse);
void	separator_parser(t_parser *parse);
void	init_parsing(t_parser *parse);
void	get_token(t_parser *parse);
void	start_parser(t_parser *parse);
void	string_parser(t_parser *parse);
void	flush_string(t_parser *parse);
void	end_parser(t_parser *parse);
void	error_parser(t_parser *parse);
void	stop_parser(t_parser *parse);
void	single_quote_parser(t_parser *parse);
void	redirect_parser(t_parser *parse);
void	pipe_parser(t_parser *parse);
void	filename_state(t_parser *parse);
void	io_redirect_parser(t_parser *parse);
void	flush_redirect(t_parser *parse);
void	delete_process(void *data);

enum	e_event
{
	NO_EVENT,
	START_GRAPH,
	END_GRAPH,
	RECALL,
	BACK,
	ERROR_GRAPH
};

struct s_graph
{
	enum e_type		*good_type;
	int				nb_of_good_type;
};

/*
************************
****  parser_debug  ****
************************
*/

void		print_token_debug(t_token *token);
void		print_arrow_debug(int which);
void		print_error_debug(enum e_type type, int which);
void		print_result_debug(int which);

/*
************************
**  set_parser_token  **
************************
*/

int			parser(t_list *lst);

void		set_start_token(t_graph *tab_tokens);
void		set_word_token(t_graph *tab_tokens);
void		set_redirect_token(t_graph *tab_tokens);
void		set_assign_token(t_graph *tab_tokens);
void		set_semicolon_token(t_graph *tab_tokens);
void		set_pipe_token(t_graph *tab_tokens);
void		set_ionumber_token(t_graph *tab_tokens);
/*
void		set_if_token(t_graph **graph);
void		set_elif_token(t_graph **graph);
void		set_else_token(t_graph **graph);
void		set_then_token(t_graph **graph);
void		set_fi_token(t_graph **graph);
void		set_bracket_open_token(t_graph **graph);
void		set_bracket_close_token(t_graph **graph);
void		set_pipe_token(t_graph **graph);
*/

/*
************************
**   generate_graph   **
************************
*/

t_graph		*generate_graph(void);

#endif
