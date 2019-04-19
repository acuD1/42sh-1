/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 13:39:31 by cempassi          #+#    #+#             */
/*   Updated: 2019/04/19 17:17:31 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "lexer.h"
# define TRUE 1
# define FALSE 0
# define PARSE_STATES 10

# define STARTING 14
# define STRING_TOKENS 16

typedef struct s_graph		t_graph;
typedef struct s_parser		t_parser;
typedef void (*t_parsing)(t_parser *);

typedef struct	s_process
{
	int		ac;
	char	**av;
	char	**env;
	int		fdin;
	int		fdout;
	int		fderror;
	pid_t	pid;
}				t_process;

typedef struct	s_job
{
	t_list			*process_list;
	pid_t			pgid;
	struct termios	*term_modes;

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
	P_SUFFIX_REDIRECT,
	P_FILENAME,
	P_IO,
	P_REDIRECT_FLUSH,
};

struct s_parser
{
	t_list				*token_list;
	enum e_parser_state	last_state;
	enum e_parser_state	state;
	t_type				last_token;
	t_process			process;
	t_list				*job_list;
	t_job				job;
	t_stack				stack;
	t_token				token;
	int					oflags;
	int					*fd;
	t_parsing			parsing[PARSE_STATES][NB_OF_TOKENS];
};

void	separator_parser(t_parser *parse);
void	init_parsing(t_parser *parse);
void	get_token(t_parser *parse);
void	start_parser(t_parser *parse);
void	string_parser(t_parser *parse);
void	flush_string(t_parser *parse);
t_list	*parser_state(t_list *token_list);
void	end_parser(t_parser *parse);
void	error_parser(t_parser *parse);
void	stop_parser(t_parser *parse);
void	single_quote_parser(t_parser *parse);
void	redirect_parser(t_parser *parse);
void	filename_state(t_parser *parse);
void	io_redirect_parser(t_parser *parse);
void	flush_redirect(t_parser *parse);

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
	t_parsing		parsing[PARSE_STATES];
	enum e_event	event;
	enum e_type		type;
	t_list			*type_end;
	t_list			*type_parent;
	t_list 			*lst;
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

void		set_start_token(t_graph *start, t_graph **tab);
void		set_string_token(t_graph **tab);
void		set_exp_token(t_graph **tab);
void		set_quote_token(t_graph **tab);
void		set_dbquote_token(t_graph **tab);
void		set_forward_token(t_graph **tab);
void		set_backward_token(t_graph **tab);
void		set_dgreat_token(t_graph **tab);
void		set_dless_token(t_graph **tab);
void		set_semicolon_token(t_graph **tab);
void		set_pipe_token(t_graph **tab);
void		set_ionumber_token(t_graph **tab);
void		set_assign_token(t_graph **tab);

/*
void		set_if_token(t_graph **tab);
void		set_elif_token(t_graph **tab);
void		set_else_token(t_graph **tab);
void		set_then_token(t_graph **tab);
void		set_fi_token(t_graph **tab);
void		set_bracket_open_token(t_graph **tab);
void		set_bracket_close_token(t_graph **tab);
void		set_pipe_token(t_graph **tab);
*/

/*
************************
**   generate_graph   **
************************
*/

t_graph		*generate_graph(void);

#endif
