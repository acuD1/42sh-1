/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 13:39:31 by cempassi          #+#    #+#             */
/*   Updated: 2019/04/18 18:02:31 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "lexer.h"
# define TRUE 1
# define FALSE 0
# define PARSE_STATES 2
# define WORD E_STRING, E_EXP, E_QUOTE, E_DB_QUOTE,
# define BASE_REDIRECT E_GREAT, E_LESS, E_DLESS, E_DGREAT,
# define AND_REDIRECT E_GREATAND, E_LESSAND,

typedef struct	s_exec
{
	int		ac;
	char	**av;
	char	**env;
	int		fdin;
	int		fdout;
	int		fderror;
	gid_t	gid;
}				t_exec;

enum	e_event
{
	NO_EVENT,
	START_GRAPH,
	END_GRAPH,
	RECALL,
	BACK,
	ERROR_GRAPH
};

enum	e_parser_state
{
	P_STRING,
	P_START,
	P_END,
};

typedef struct s_graph	t_graph;
typedef struct s_parser	t_parser;
typedef void (*t_parsing)(t_parser *);

struct s_parser
{
	t_list				*token_list;
	enum e_parser_state state;
	t_exec				current_exec;
	t_list				*parse_output;
	t_token				*token;
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
