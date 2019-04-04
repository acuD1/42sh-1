#ifndef PARSER_H
# define PARSER_H

# include "lexer.h"
# define NB_OF_TOKENS 39
# define TRUE 1
# define FALSE 0

enum	e_event
{
	NO_EVENT,
	START_GRAPH,
	END_GRAPH,
	RECALL,
	BACK,
	ERROR_GRAPH
};

typedef struct s_graph	t_graph;

struct s_graph
{
	enum	e_event	event;
	enum	e_type	type;
	t_list			*type_end;
	t_list			*type_parent;
	t_list 			*lst;
};

/*
************************
****  parser_debug  ****
************************
*/

void		print_token_debug(enum e_type type);
void		print_arrow_debug(int which);
void		print_error_debug(enum e_type type, int which);
void		print_result_debug(int which);

/*
************************
**  set_parser_token  **
************************
*/

void		set_start_token(t_graph *start, t_graph **tab);
void		set_string_token(t_graph *start, t_graph **tab);
void		set_if_token(t_graph *start, t_graph **tab);
void		set_elif_token(t_graph *start, t_graph **tab);
void		set_else_token(t_graph *start, t_graph **tab);
void		set_fi_token(t_graph *start, t_graph **tab);
void		set_bracket_open_token(t_graph *start, t_graph **tab);
void		set_bracket_close_token(t_graph *start, t_graph **tab);

/*
************************
**   generate_graph   **
************************
*/

t_graph		*generate_graph(void);

#endif
