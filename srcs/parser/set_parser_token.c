#include "parser.h"

void		set_start_token(t_graph *start, t_graph **graph)
{
	static enum e_type type[12] = {E_STRING, E_EXP, E_GREAT,
				E_DGREAT, E_LESS, E_DLESS, E_QUOTE, E_DB_QUOTE, E_SEMICOLON,
				E_IO_NUMBER, E_ASSIGN, E_END};
	int		i;

	i = 0;
	while (i < 12)
		ft_lstadd(&start->lst, ft_lstnew(&graph[type[i++]], sizeof(t_graph **)));
}

void		set_string_token(t_graph **graph)
{
	ft_lstadd(&graph[E_STRING]->lst, ft_lstnew(&graph[E_STRING], sizeof(t_graph **)));
	ft_lstadd(&graph[E_STRING]->lst, ft_lstnew(&graph[E_EXP], sizeof(t_graph **)));
	ft_lstadd(&graph[E_STRING]->lst, ft_lstnew(&graph[E_GREAT], sizeof(t_graph **)));
	ft_lstadd(&graph[E_STRING]->lst, ft_lstnew(&graph[E_DGREAT], sizeof(t_graph **)));
	ft_lstadd(&graph[E_STRING]->lst, ft_lstnew(&graph[E_LESS], sizeof(t_graph **)));
	ft_lstadd(&graph[E_STRING]->lst, ft_lstnew(&graph[E_DLESS], sizeof(t_graph **)));
	ft_lstadd(&graph[E_STRING]->lst, ft_lstnew(&graph[E_QUOTE], sizeof(t_graph **)));
	ft_lstadd(&graph[E_STRING]->lst, ft_lstnew(&graph[E_DB_QUOTE], sizeof(t_graph **)));
	ft_lstadd(&graph[E_STRING]->lst, ft_lstnew(&graph[E_SEMICOLON], sizeof(t_graph **)));
	ft_lstadd(&graph[E_STRING]->lst, ft_lstnew(&graph[E_PIPE], sizeof(t_graph **)));
	ft_lstadd(&graph[E_STRING]->lst, ft_lstnew(&graph[E_END], sizeof(t_graph **)));
	ft_lstadd(&graph[E_STRING]->lst, ft_lstnew(&graph[E_IO_NUMBER], sizeof(t_graph **)));
	ft_lstadd(&graph[E_STRING]->lst, ft_lstnew(&graph[E_ASSIGN], sizeof(t_graph **)));
}

void		set_exp_token(t_graph **graph)
{
	ft_lstadd(&graph[E_EXP]->lst, ft_lstnew(&graph[E_STRING], sizeof(t_graph **)));
	ft_lstadd(&graph[E_EXP]->lst, ft_lstnew(&graph[E_EXP], sizeof(t_graph **)));
	ft_lstadd(&graph[E_EXP]->lst, ft_lstnew(&graph[E_GREAT], sizeof(t_graph **)));
	ft_lstadd(&graph[E_EXP]->lst, ft_lstnew(&graph[E_DGREAT], sizeof(t_graph **)));
	ft_lstadd(&graph[E_EXP]->lst, ft_lstnew(&graph[E_LESS], sizeof(t_graph **)));
	ft_lstadd(&graph[E_EXP]->lst, ft_lstnew(&graph[E_DLESS], sizeof(t_graph **)));
	ft_lstadd(&graph[E_EXP]->lst, ft_lstnew(&graph[E_QUOTE], sizeof(t_graph **)));
	ft_lstadd(&graph[E_EXP]->lst, ft_lstnew(&graph[E_DB_QUOTE], sizeof(t_graph **)));
	ft_lstadd(&graph[E_EXP]->lst, ft_lstnew(&graph[E_SEMICOLON], sizeof(t_graph **)));
	ft_lstadd(&graph[E_EXP]->lst, ft_lstnew(&graph[E_PIPE], sizeof(t_graph **)));
	ft_lstadd(&graph[E_EXP]->lst, ft_lstnew(&graph[E_END], sizeof(t_graph **)));
	ft_lstadd(&graph[E_EXP]->lst, ft_lstnew(&graph[E_IO_NUMBER], sizeof(t_graph **)));
	ft_lstadd(&graph[E_EXP]->lst, ft_lstnew(&graph[E_ASSIGN], sizeof(t_graph **)));
}

void		set_quote_token(t_graph **graph)
{
	ft_lstadd(&graph[E_QUOTE]->lst, ft_lstnew(&graph[E_STRING], sizeof(t_graph **)));
	ft_lstadd(&graph[E_QUOTE]->lst, ft_lstnew(&graph[E_EXP], sizeof(t_graph **)));
	ft_lstadd(&graph[E_QUOTE]->lst, ft_lstnew(&graph[E_GREAT], sizeof(t_graph **)));
	ft_lstadd(&graph[E_QUOTE]->lst, ft_lstnew(&graph[E_DGREAT], sizeof(t_graph **)));
	ft_lstadd(&graph[E_QUOTE]->lst, ft_lstnew(&graph[E_LESS], sizeof(t_graph **)));
	ft_lstadd(&graph[E_QUOTE]->lst, ft_lstnew(&graph[E_DLESS], sizeof(t_graph **)));
	ft_lstadd(&graph[E_QUOTE]->lst, ft_lstnew(&graph[E_QUOTE], sizeof(t_graph **)));
	ft_lstadd(&graph[E_QUOTE]->lst, ft_lstnew(&graph[E_DB_QUOTE], sizeof(t_graph **)));
	ft_lstadd(&graph[E_QUOTE]->lst, ft_lstnew(&graph[E_SEMICOLON], sizeof(t_graph **)));
	ft_lstadd(&graph[E_QUOTE]->lst, ft_lstnew(&graph[E_PIPE], sizeof(t_graph **)));
	ft_lstadd(&graph[E_QUOTE]->lst, ft_lstnew(&graph[E_END], sizeof(t_graph **)));
	ft_lstadd(&graph[E_QUOTE]->lst, ft_lstnew(&graph[E_IO_NUMBER], sizeof(t_graph **)));
	ft_lstadd(&graph[E_QUOTE]->lst, ft_lstnew(&graph[E_ASSIGN], sizeof(t_graph **)));
}

void		set_dbquote_token(t_graph **graph)
{
	ft_lstadd(&graph[E_DB_QUOTE]->lst, ft_lstnew(&graph[E_STRING], sizeof(t_graph **)));
	ft_lstadd(&graph[E_DB_QUOTE]->lst, ft_lstnew(&graph[E_EXP], sizeof(t_graph **)));
	ft_lstadd(&graph[E_DB_QUOTE]->lst, ft_lstnew(&graph[E_GREAT], sizeof(t_graph **)));
	ft_lstadd(&graph[E_DB_QUOTE]->lst, ft_lstnew(&graph[E_DGREAT], sizeof(t_graph **)));
	ft_lstadd(&graph[E_DB_QUOTE]->lst, ft_lstnew(&graph[E_LESS], sizeof(t_graph **)));
	ft_lstadd(&graph[E_DB_QUOTE]->lst, ft_lstnew(&graph[E_DLESS], sizeof(t_graph **)));
	ft_lstadd(&graph[E_DB_QUOTE]->lst, ft_lstnew(&graph[E_QUOTE], sizeof(t_graph **)));
	ft_lstadd(&graph[E_DB_QUOTE]->lst, ft_lstnew(&graph[E_DB_QUOTE], sizeof(t_graph **)));
	ft_lstadd(&graph[E_DB_QUOTE]->lst, ft_lstnew(&graph[E_SEMICOLON], sizeof(t_graph **)));
	ft_lstadd(&graph[E_DB_QUOTE]->lst, ft_lstnew(&graph[E_PIPE], sizeof(t_graph **)));
	ft_lstadd(&graph[E_DB_QUOTE]->lst, ft_lstnew(&graph[E_END], sizeof(t_graph **)));
	ft_lstadd(&graph[E_DB_QUOTE]->lst, ft_lstnew(&graph[E_IO_NUMBER], sizeof(t_graph **)));
	ft_lstadd(&graph[E_DB_QUOTE]->lst, ft_lstnew(&graph[E_ASSIGN], sizeof(t_graph **)));
}

void		set_forward_token(t_graph **graph)
{
	ft_lstadd(&graph[E_GREAT]->lst, ft_lstnew(&graph[E_STRING], sizeof(t_graph **)));
	ft_lstadd(&graph[E_GREAT]->lst, ft_lstnew(&graph[E_EXP], sizeof(t_graph **)));
	ft_lstadd(&graph[E_GREAT]->lst, ft_lstnew(&graph[E_QUOTE], sizeof(t_graph **)));
	ft_lstadd(&graph[E_GREAT]->lst, ft_lstnew(&graph[E_DB_QUOTE], sizeof(t_graph **)));
}

void		set_backward_token(t_graph **graph)
{
	ft_lstadd(&graph[E_LESS]->lst, ft_lstnew(&graph[E_STRING], sizeof(t_graph **)));
	ft_lstadd(&graph[E_LESS]->lst, ft_lstnew(&graph[E_EXP], sizeof(t_graph **)));
	ft_lstadd(&graph[E_LESS]->lst, ft_lstnew(&graph[E_QUOTE], sizeof(t_graph **)));
	ft_lstadd(&graph[E_LESS]->lst, ft_lstnew(&graph[E_DB_QUOTE], sizeof(t_graph **)));
}

void		set_dgreat_token(t_graph **graph)
{
	ft_lstadd(&graph[E_DGREAT]->lst, ft_lstnew(&graph[E_STRING], sizeof(t_graph **)));
	ft_lstadd(&graph[E_DGREAT]->lst, ft_lstnew(&graph[E_EXP], sizeof(t_graph **)));
	ft_lstadd(&graph[E_DGREAT]->lst, ft_lstnew(&graph[E_QUOTE], sizeof(t_graph **)));
	ft_lstadd(&graph[E_DGREAT]->lst, ft_lstnew(&graph[E_DB_QUOTE], sizeof(t_graph **)));
}

void		set_dless_token(t_graph **graph)
{
	ft_lstadd(&graph[E_DLESS]->lst, ft_lstnew(&graph[E_STRING], sizeof(t_graph **)));
	ft_lstadd(&graph[E_DLESS]->lst, ft_lstnew(&graph[E_EXP], sizeof(t_graph **)));
	ft_lstadd(&graph[E_DLESS]->lst, ft_lstnew(&graph[E_QUOTE], sizeof(t_graph **)));
	ft_lstadd(&graph[E_DLESS]->lst, ft_lstnew(&graph[E_DB_QUOTE], sizeof(t_graph **)));
}

void		set_assign_token(t_graph **graph)
{
	ft_lstadd(&graph[E_ASSIGN]->lst, ft_lstnew(&graph[E_STRING], sizeof(t_graph **)));
	ft_lstadd(&graph[E_ASSIGN]->lst, ft_lstnew(&graph[E_EXP], sizeof(t_graph **)));
	ft_lstadd(&graph[E_ASSIGN]->lst, ft_lstnew(&graph[E_QUOTE], sizeof(t_graph **)));
	ft_lstadd(&graph[E_ASSIGN]->lst, ft_lstnew(&graph[E_DB_QUOTE], sizeof(t_graph **)));
}

void		set_semicolon_token(t_graph **graph)
{
	ft_lstadd(&graph[E_SEMICOLON]->lst, ft_lstnew(&graph[E_STRING], sizeof(t_graph **)));
	ft_lstadd(&graph[E_SEMICOLON]->lst, ft_lstnew(&graph[E_EXP], sizeof(t_graph **)));
	ft_lstadd(&graph[E_SEMICOLON]->lst, ft_lstnew(&graph[E_GREAT], sizeof(t_graph **)));
	ft_lstadd(&graph[E_SEMICOLON]->lst, ft_lstnew(&graph[E_DGREAT], sizeof(t_graph **)));
	ft_lstadd(&graph[E_SEMICOLON]->lst, ft_lstnew(&graph[E_LESS], sizeof(t_graph **)));
	ft_lstadd(&graph[E_SEMICOLON]->lst, ft_lstnew(&graph[E_DLESS], sizeof(t_graph **)));
	ft_lstadd(&graph[E_SEMICOLON]->lst, ft_lstnew(&graph[E_QUOTE], sizeof(t_graph **)));
	ft_lstadd(&graph[E_SEMICOLON]->lst, ft_lstnew(&graph[E_DB_QUOTE], sizeof(t_graph **)));
	ft_lstadd(&graph[E_SEMICOLON]->lst, ft_lstnew(&graph[E_SEMICOLON], sizeof(t_graph **)));
	ft_lstadd(&graph[E_SEMICOLON]->lst, ft_lstnew(&graph[E_IO_NUMBER], sizeof(t_graph **)));
	ft_lstadd(&graph[E_SEMICOLON]->lst, ft_lstnew(&graph[E_END], sizeof(t_graph **)));
}

void		set_pipe_token(t_graph **graph)
{
	ft_lstadd(&graph[E_PIPE]->lst, ft_lstnew(&graph[E_STRING], sizeof(t_graph **)));
	ft_lstadd(&graph[E_PIPE]->lst, ft_lstnew(&graph[E_EXP], sizeof(t_graph **)));
	ft_lstadd(&graph[E_PIPE]->lst, ft_lstnew(&graph[E_GREAT], sizeof(t_graph **)));
	ft_lstadd(&graph[E_PIPE]->lst, ft_lstnew(&graph[E_DGREAT], sizeof(t_graph **)));
	ft_lstadd(&graph[E_PIPE]->lst, ft_lstnew(&graph[E_LESS], sizeof(t_graph **)));
	ft_lstadd(&graph[E_PIPE]->lst, ft_lstnew(&graph[E_DLESS], sizeof(t_graph **)));
	ft_lstadd(&graph[E_PIPE]->lst, ft_lstnew(&graph[E_QUOTE], sizeof(t_graph **)));
	ft_lstadd(&graph[E_PIPE]->lst, ft_lstnew(&graph[E_DB_QUOTE], sizeof(t_graph **)));
	ft_lstadd(&graph[E_PIPE]->lst, ft_lstnew(&graph[E_IO_NUMBER], sizeof(t_graph **)));
	ft_lstadd(&graph[E_PIPE]->lst, ft_lstnew(&graph[E_ASSIGN], sizeof(t_graph **)));
}

void		set_ionumber_token(t_graph **graph)
{
	ft_lstadd(&graph[E_IO_NUMBER]->lst, ft_lstnew(&graph[E_GREAT], sizeof(t_graph **)));
	ft_lstadd(&graph[E_IO_NUMBER]->lst, ft_lstnew(&graph[E_LESS], sizeof(t_graph **)));
	ft_lstadd(&graph[E_IO_NUMBER]->lst, ft_lstnew(&graph[E_DGREAT], sizeof(t_graph **)));
	ft_lstadd(&graph[E_IO_NUMBER]->lst, ft_lstnew(&graph[E_DLESS], sizeof(t_graph **)));
}

/*
void		set_start_token(t_graph *start, t_graph **graph)
{
	start->end = 1;
	ft_lstadd(&start->lst, ft_lstnew(&graph[E_STRING], sizeof(t_graph **)));
	ft_lstadd(&start->lst, ft_lstnew(&graph[E_IF], sizeof(t_graph **)));
	ft_lstadd(&start->lst, ft_lstnew(&graph[E_QUOTE], sizeof(t_graph **)));
	ft_lstadd(&start->lst, ft_lstnew(&graph[E_DB_QUOTE], sizeof(t_graph **)));
}

void		set_string_token(t_graph **graph)
{
	graph[E_STRING]->end = 1;
	ft_lstadd(&graph[E_STRING]->lst, ft_lstnew(&graph[E_QUOTE], sizeof(t_graph **)));
	ft_lstadd(&graph[E_STRING]->lst, ft_lstnew(&graph[E_DB_QUOTE], sizeof(t_graph **)));
	ft_lstadd(&graph[E_STRING]->lst, ft_lstnew(&graph[E_STRING], sizeof(t_graph **)));
	ft_lstadd(&graph[E_STRING]->lst, ft_lstnew(&graph[E_IF], sizeof(t_graph **)));
	ft_lstadd(&graph[E_STRING]->lst, ft_lstnew(&graph[E_ELIF], sizeof(t_graph **)));
	ft_lstadd(&graph[E_STRING]->lst, ft_lstnew(&graph[E_ELSE], sizeof(t_graph **)));
	ft_lstadd(&graph[E_STRING]->lst, ft_lstnew(&graph[E_FI], sizeof(t_graph **)));
	ft_lstadd(&graph[E_STRING]->lst, ft_lstnew(&graph[E_BRACKET_CLOSE], sizeof(t_graph **)));
	ft_lstadd(&graph[E_STRING]->lst, ft_lstnew(&graph[E_PIPE], sizeof(t_graph **)));
}

void		set_quote_token(t_graph **graph)
{
	graph[E_QUOTE]->end = 1;
	ft_lstadd(&graph[E_QUOTE]->lst, ft_lstnew(&graph[E_QUOTE], sizeof(t_graph **)));
	ft_lstadd(&graph[E_QUOTE]->lst, ft_lstnew(&graph[E_DB_QUOTE], sizeof(t_graph **)));
	ft_lstadd(&graph[E_QUOTE]->lst, ft_lstnew(&graph[E_STRING], sizeof(t_graph **)));
	ft_lstadd(&graph[E_QUOTE]->lst, ft_lstnew(&graph[E_IF], sizeof(t_graph **)));
	ft_lstadd(&graph[E_QUOTE]->lst, ft_lstnew(&graph[E_ELIF], sizeof(t_graph **)));
	ft_lstadd(&graph[E_QUOTE]->lst, ft_lstnew(&graph[E_ELSE], sizeof(t_graph **)));
	ft_lstadd(&graph[E_QUOTE]->lst, ft_lstnew(&graph[E_FI], sizeof(t_graph **)));
	ft_lstadd(&graph[E_QUOTE]->lst, ft_lstnew(&graph[E_BRACKET_CLOSE], sizeof(t_graph **)));
	ft_lstadd(&graph[E_QUOTE]->lst, ft_lstnew(&graph[E_PIPE], sizeof(t_graph **)));
}

void		set_dbquote_token(t_graph **graph)
{
	graph[E_DB_QUOTE]->end = 1;
	ft_lstadd(&graph[E_DB_QUOTE]->lst, ft_lstnew(&graph[E_QUOTE], sizeof(t_graph **)));
	ft_lstadd(&graph[E_DB_QUOTE]->lst, ft_lstnew(&graph[E_DB_QUOTE], sizeof(t_graph **)));
	ft_lstadd(&graph[E_DB_QUOTE]->lst, ft_lstnew(&graph[E_STRING], sizeof(t_graph **)));
	ft_lstadd(&graph[E_DB_QUOTE]->lst, ft_lstnew(&graph[E_IF], sizeof(t_graph **)));
	ft_lstadd(&graph[E_DB_QUOTE]->lst, ft_lstnew(&graph[E_ELIF], sizeof(t_graph **)));
	ft_lstadd(&graph[E_DB_QUOTE]->lst, ft_lstnew(&graph[E_ELSE], sizeof(t_graph **)));
	ft_lstadd(&graph[E_DB_QUOTE]->lst, ft_lstnew(&graph[E_FI], sizeof(t_graph **)));
	ft_lstadd(&graph[E_DB_QUOTE]->lst, ft_lstnew(&graph[E_BRACKET_CLOSE], sizeof(t_graph **)));
	ft_lstadd(&graph[E_DB_QUOTE]->lst, ft_lstnew(&graph[E_PIPE], sizeof(t_graph **)));
}

void		set_pipe_token(t_graph **graph)
{
	graph[E_PIPE]->event = START_GRAPH;
	ft_lstadd(&graph[E_PIPE]->lst, ft_lstnew(&graph[E_STRING], sizeof(t_graph **)));
	ft_lstadd(&graph[E_PIPE]->lst, ft_lstnew(&graph[E_QUOTE], sizeof(t_graph **)));
	ft_lstadd(&graph[E_PIPE]->lst, ft_lstnew(&graph[E_DB_QUOTE], sizeof(t_graph **)));
}

void		set_if_token(t_graph **graph)
{
	enum e_type	type_end;

	graph[E_IF]->event = RECALL;

	type_end = E_THEN;
	ft_lstadd(&graph[E_IF]->type_end, ft_lstnew(&type_end, sizeof(enum e_type *)));

	ft_lstadd(&graph[E_IF]->lst, ft_lstnew(&graph[E_BRACKET_OPEN], sizeof(t_graph **)));
}

void		set_elif_token(t_graph **graph)
{
	enum e_type	type_end;
	enum e_type	type_parent;

	graph[E_ELIF]->event = RECALL;

	type_end = E_THEN;
	ft_lstadd(&graph[E_ELIF]->type_end, ft_lstnew(&type_end, sizeof(enum e_type *)));

	type_parent = E_IF;
	ft_lstadd(&graph[E_ELIF]->type_parent, ft_lstnew(&type_parent, sizeof(enum e_type *)));

	ft_lstadd(&graph[E_ELIF]->lst, ft_lstnew(&graph[E_BRACKET_OPEN], sizeof(t_graph **)));
}

void		set_else_token(t_graph **graph)
{
	enum e_type	type_end;
	enum e_type	type_parent;

	graph[E_ELSE]->event = RECALL;

	type_end = E_FI;
	ft_lstadd(&graph[E_ELSE]->type_end, ft_lstnew(&type_end, sizeof(enum e_type *)));

	type_parent = E_IF;
	ft_lstadd(&graph[E_ELSE]->type_parent, ft_lstnew(&type_parent, sizeof(enum e_type *)));

	ft_lstadd(&graph[E_ELSE]->lst, ft_lstnew(&graph[E_STRING], sizeof(t_graph **)));
	ft_lstadd(&graph[E_ELSE]->lst, ft_lstnew(&graph[E_QUOTE], sizeof(t_graph **)));
	ft_lstadd(&graph[E_ELSE]->lst, ft_lstnew(&graph[E_DB_QUOTE], sizeof(t_graph **)));
}

void		set_fi_token(t_graph **graph)
{
	graph[E_FI]->end = 1;
	graph[E_FI]->event = BACK;
	ft_lstadd(&graph[E_FI]->lst, ft_lstnew(&graph[E_STRING], sizeof(t_graph **)));
	ft_lstadd(&graph[E_FI]->lst, ft_lstnew(&graph[E_QUOTE], sizeof(t_graph **)));
	ft_lstadd(&graph[E_FI]->lst, ft_lstnew(&graph[E_DB_QUOTE], sizeof(t_graph **)));
	ft_lstadd(&graph[E_FI]->lst, ft_lstnew(&graph[E_FI], sizeof(t_graph **)));
	ft_lstadd(&graph[E_FI]->lst, ft_lstnew(&graph[E_IF], sizeof(t_graph **)));
}

void		set_then_token(t_graph **graph)
{
	enum e_type	type_end;
	enum e_type	type_parent;

	graph[E_THEN]->event = RECALL;

	type_end = E_FI;
	ft_lstadd(&graph[E_THEN]->type_end, ft_lstnew(&type_end, sizeof(enum e_type *)));
	type_end = E_ELIF;
	ft_lstadd(&graph[E_THEN]->type_end, ft_lstnew(&type_end, sizeof(enum e_type *)));
	type_end = E_ELSE;
	ft_lstadd(&graph[E_THEN]->type_end, ft_lstnew(&type_end, sizeof(enum e_type *)));

	type_parent = E_IF;
	ft_lstadd(&graph[E_THEN]->type_parent, ft_lstnew(&type_parent, sizeof(enum e_type *)));

	ft_lstadd(&graph[E_THEN]->lst, ft_lstnew(&graph[E_STRING], sizeof(t_graph **)));
	ft_lstadd(&graph[E_THEN]->lst, ft_lstnew(&graph[E_QUOTE], sizeof(t_graph **)));
	ft_lstadd(&graph[E_THEN]->lst, ft_lstnew(&graph[E_DB_QUOTE], sizeof(t_graph **)));
}

void		set_bracket_open_token(t_graph **graph)
{
	enum e_type	type_end;

	graph[E_BRACKET_OPEN]->event = RECALL;

	type_end = E_BRACKET_CLOSE;
	ft_lstadd(&graph[E_BRACKET_OPEN]->type_end, ft_lstnew(&type_end, sizeof(enum e_type *)));

	ft_lstadd(&graph[E_BRACKET_OPEN]->lst, ft_lstnew(&graph[E_STRING], sizeof(t_graph **)));
	ft_lstadd(&graph[E_BRACKET_OPEN]->lst, ft_lstnew(&graph[E_QUOTE], sizeof(t_graph **)));
	ft_lstadd(&graph[E_BRACKET_OPEN]->lst, ft_lstnew(&graph[E_DB_QUOTE], sizeof(t_graph **)));
}

void		set_bracket_close_token(t_graph **graph)
{
	graph[E_BRACKET_CLOSE]->event = BACK;
	ft_lstadd(&graph[E_BRACKET_CLOSE]->lst, ft_lstnew(&graph[E_THEN], sizeof(t_graph **)));
	ft_lstadd(&graph[E_BRACKET_CLOSE]->lst, ft_lstnew(&graph[E_BRACKET_OPEN], sizeof(t_graph **)));
}
*/
