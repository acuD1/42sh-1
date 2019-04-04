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
	RECALL
};

typedef struct s_graph	t_graph;

struct s_graph
{
	enum	e_event	event;
	enum	e_type	type;
	enum	e_type	type_end;
	t_list 			*lst;
};

void		print_token(enum e_type type);

void		set_start_token(t_graph *start, t_graph **tab);
void		set_string_token(t_graph *start, t_graph **tab);
void		set_if_token(t_graph *start, t_graph **tab);
void		set_fi_token(t_graph *start, t_graph **tab);
void		set_bracket_open_token(t_graph *start, t_graph **tab);
void		set_bracket_close_token(t_graph *start, t_graph **tab);

#endif
