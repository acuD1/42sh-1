#include "parser.h"

void		set_start_token(t_graph *start, t_graph **tab)
{
	ft_lstadd(&start->lst, ft_lstnew(&tab[E_STRING], sizeof(t_graph **)));
	ft_lstadd(&start->lst, ft_lstnew(&tab[E_EXP], sizeof(t_graph **)));
	ft_lstadd(&start->lst, ft_lstnew(&tab[E_FORWARD], sizeof(t_graph **)));
	ft_lstadd(&start->lst, ft_lstnew(&tab[E_DGREAT], sizeof(t_graph **)));
	ft_lstadd(&start->lst, ft_lstnew(&tab[E_BACKWARD], sizeof(t_graph **)));
	ft_lstadd(&start->lst, ft_lstnew(&tab[E_DLESS], sizeof(t_graph **)));
	ft_lstadd(&start->lst, ft_lstnew(&tab[E_QUOTE], sizeof(t_graph **)));
	ft_lstadd(&start->lst, ft_lstnew(&tab[E_DB_QUOTE], sizeof(t_graph **)));
	ft_lstadd(&start->lst, ft_lstnew(&tab[E_SEMICOLON], sizeof(t_graph **)));
	ft_lstadd(&start->lst, ft_lstnew(&tab[E_IO_NUMBER], sizeof(t_graph **)));
	ft_lstadd(&start->lst, ft_lstnew(&tab[E_END], sizeof(t_graph **)));
}

void		set_string_token(t_graph **tab)
{
	ft_lstadd(&tab[E_STRING]->lst, ft_lstnew(&tab[E_STRING], sizeof(t_graph **)));
	ft_lstadd(&tab[E_STRING]->lst, ft_lstnew(&tab[E_EXP], sizeof(t_graph **)));
	ft_lstadd(&tab[E_STRING]->lst, ft_lstnew(&tab[E_FORWARD], sizeof(t_graph **)));
	ft_lstadd(&tab[E_STRING]->lst, ft_lstnew(&tab[E_DGREAT], sizeof(t_graph **)));
	ft_lstadd(&tab[E_STRING]->lst, ft_lstnew(&tab[E_BACKWARD], sizeof(t_graph **)));
	ft_lstadd(&tab[E_STRING]->lst, ft_lstnew(&tab[E_DLESS], sizeof(t_graph **)));
	ft_lstadd(&tab[E_STRING]->lst, ft_lstnew(&tab[E_QUOTE], sizeof(t_graph **)));
	ft_lstadd(&tab[E_STRING]->lst, ft_lstnew(&tab[E_DB_QUOTE], sizeof(t_graph **)));
	ft_lstadd(&tab[E_STRING]->lst, ft_lstnew(&tab[E_SEMICOLON], sizeof(t_graph **)));
	ft_lstadd(&tab[E_STRING]->lst, ft_lstnew(&tab[E_PIPE], sizeof(t_graph **)));
	ft_lstadd(&tab[E_STRING]->lst, ft_lstnew(&tab[E_END], sizeof(t_graph **)));
	ft_lstadd(&tab[E_STRING]->lst, ft_lstnew(&tab[E_IO_NUMBER], sizeof(t_graph **)));
	ft_lstadd(&tab[E_STRING]->lst, ft_lstnew(&tab[E_ASSIGN], sizeof(t_graph **)));
}

void		set_exp_token(t_graph **tab)
{
	ft_lstadd(&tab[E_EXP]->lst, ft_lstnew(&tab[E_STRING], sizeof(t_graph **)));
	ft_lstadd(&tab[E_EXP]->lst, ft_lstnew(&tab[E_EXP], sizeof(t_graph **)));
	ft_lstadd(&tab[E_EXP]->lst, ft_lstnew(&tab[E_FORWARD], sizeof(t_graph **)));
	ft_lstadd(&tab[E_EXP]->lst, ft_lstnew(&tab[E_DGREAT], sizeof(t_graph **)));
	ft_lstadd(&tab[E_EXP]->lst, ft_lstnew(&tab[E_BACKWARD], sizeof(t_graph **)));
	ft_lstadd(&tab[E_EXP]->lst, ft_lstnew(&tab[E_DLESS], sizeof(t_graph **)));
	ft_lstadd(&tab[E_EXP]->lst, ft_lstnew(&tab[E_QUOTE], sizeof(t_graph **)));
	ft_lstadd(&tab[E_EXP]->lst, ft_lstnew(&tab[E_DB_QUOTE], sizeof(t_graph **)));
	ft_lstadd(&tab[E_EXP]->lst, ft_lstnew(&tab[E_SEMICOLON], sizeof(t_graph **)));
	ft_lstadd(&tab[E_EXP]->lst, ft_lstnew(&tab[E_PIPE], sizeof(t_graph **)));
	ft_lstadd(&tab[E_EXP]->lst, ft_lstnew(&tab[E_END], sizeof(t_graph **)));
	ft_lstadd(&tab[E_EXP]->lst, ft_lstnew(&tab[E_IO_NUMBER], sizeof(t_graph **)));
	ft_lstadd(&tab[E_EXP]->lst, ft_lstnew(&tab[E_ASSIGN], sizeof(t_graph **)));
}

void		set_quote_token(t_graph **tab)
{
	ft_lstadd(&tab[E_QUOTE]->lst, ft_lstnew(&tab[E_STRING], sizeof(t_graph **)));
	ft_lstadd(&tab[E_QUOTE]->lst, ft_lstnew(&tab[E_EXP], sizeof(t_graph **)));
	ft_lstadd(&tab[E_QUOTE]->lst, ft_lstnew(&tab[E_FORWARD], sizeof(t_graph **)));
	ft_lstadd(&tab[E_QUOTE]->lst, ft_lstnew(&tab[E_DGREAT], sizeof(t_graph **)));
	ft_lstadd(&tab[E_QUOTE]->lst, ft_lstnew(&tab[E_BACKWARD], sizeof(t_graph **)));
	ft_lstadd(&tab[E_QUOTE]->lst, ft_lstnew(&tab[E_DLESS], sizeof(t_graph **)));
	ft_lstadd(&tab[E_QUOTE]->lst, ft_lstnew(&tab[E_QUOTE], sizeof(t_graph **)));
	ft_lstadd(&tab[E_QUOTE]->lst, ft_lstnew(&tab[E_DB_QUOTE], sizeof(t_graph **)));
	ft_lstadd(&tab[E_QUOTE]->lst, ft_lstnew(&tab[E_SEMICOLON], sizeof(t_graph **)));
	ft_lstadd(&tab[E_QUOTE]->lst, ft_lstnew(&tab[E_PIPE], sizeof(t_graph **)));
	ft_lstadd(&tab[E_QUOTE]->lst, ft_lstnew(&tab[E_END], sizeof(t_graph **)));
	ft_lstadd(&tab[E_QUOTE]->lst, ft_lstnew(&tab[E_IO_NUMBER], sizeof(t_graph **)));
	ft_lstadd(&tab[E_QUOTE]->lst, ft_lstnew(&tab[E_ASSIGN], sizeof(t_graph **)));
}

void		set_dbquote_token(t_graph **tab)
{
	ft_lstadd(&tab[E_DB_QUOTE]->lst, ft_lstnew(&tab[E_STRING], sizeof(t_graph **)));
	ft_lstadd(&tab[E_DB_QUOTE]->lst, ft_lstnew(&tab[E_EXP], sizeof(t_graph **)));
	ft_lstadd(&tab[E_DB_QUOTE]->lst, ft_lstnew(&tab[E_FORWARD], sizeof(t_graph **)));
	ft_lstadd(&tab[E_DB_QUOTE]->lst, ft_lstnew(&tab[E_DGREAT], sizeof(t_graph **)));
	ft_lstadd(&tab[E_DB_QUOTE]->lst, ft_lstnew(&tab[E_BACKWARD], sizeof(t_graph **)));
	ft_lstadd(&tab[E_DB_QUOTE]->lst, ft_lstnew(&tab[E_DLESS], sizeof(t_graph **)));
	ft_lstadd(&tab[E_DB_QUOTE]->lst, ft_lstnew(&tab[E_QUOTE], sizeof(t_graph **)));
	ft_lstadd(&tab[E_DB_QUOTE]->lst, ft_lstnew(&tab[E_DB_QUOTE], sizeof(t_graph **)));
	ft_lstadd(&tab[E_DB_QUOTE]->lst, ft_lstnew(&tab[E_SEMICOLON], sizeof(t_graph **)));
	ft_lstadd(&tab[E_DB_QUOTE]->lst, ft_lstnew(&tab[E_PIPE], sizeof(t_graph **)));
	ft_lstadd(&tab[E_DB_QUOTE]->lst, ft_lstnew(&tab[E_END], sizeof(t_graph **)));
	ft_lstadd(&tab[E_DB_QUOTE]->lst, ft_lstnew(&tab[E_IO_NUMBER], sizeof(t_graph **)));
	ft_lstadd(&tab[E_DB_QUOTE]->lst, ft_lstnew(&tab[E_ASSIGN], sizeof(t_graph **)));
}

void		set_forward_token(t_graph **tab)
{
	ft_lstadd(&tab[E_FORWARD]->lst, ft_lstnew(&tab[E_STRING], sizeof(t_graph **)));
	ft_lstadd(&tab[E_FORWARD]->lst, ft_lstnew(&tab[E_EXP], sizeof(t_graph **)));
	ft_lstadd(&tab[E_FORWARD]->lst, ft_lstnew(&tab[E_QUOTE], sizeof(t_graph **)));
	ft_lstadd(&tab[E_FORWARD]->lst, ft_lstnew(&tab[E_DB_QUOTE], sizeof(t_graph **)));
}

void		set_backward_token(t_graph **tab)
{
	ft_lstadd(&tab[E_BACKWARD]->lst, ft_lstnew(&tab[E_STRING], sizeof(t_graph **)));
	ft_lstadd(&tab[E_BACKWARD]->lst, ft_lstnew(&tab[E_EXP], sizeof(t_graph **)));
	ft_lstadd(&tab[E_BACKWARD]->lst, ft_lstnew(&tab[E_QUOTE], sizeof(t_graph **)));
	ft_lstadd(&tab[E_BACKWARD]->lst, ft_lstnew(&tab[E_DB_QUOTE], sizeof(t_graph **)));
}

void		set_dgreat_token(t_graph **tab)
{
	ft_lstadd(&tab[E_DGREAT]->lst, ft_lstnew(&tab[E_STRING], sizeof(t_graph **)));
	ft_lstadd(&tab[E_DGREAT]->lst, ft_lstnew(&tab[E_EXP], sizeof(t_graph **)));
	ft_lstadd(&tab[E_DGREAT]->lst, ft_lstnew(&tab[E_QUOTE], sizeof(t_graph **)));
	ft_lstadd(&tab[E_DGREAT]->lst, ft_lstnew(&tab[E_DB_QUOTE], sizeof(t_graph **)));
}

void		set_dless_token(t_graph **tab)
{
	ft_lstadd(&tab[E_DLESS]->lst, ft_lstnew(&tab[E_STRING], sizeof(t_graph **)));
	ft_lstadd(&tab[E_DLESS]->lst, ft_lstnew(&tab[E_EXP], sizeof(t_graph **)));
	ft_lstadd(&tab[E_DLESS]->lst, ft_lstnew(&tab[E_QUOTE], sizeof(t_graph **)));
	ft_lstadd(&tab[E_DLESS]->lst, ft_lstnew(&tab[E_DB_QUOTE], sizeof(t_graph **)));
}

void		set_assign_token(t_graph **tab)
{
	ft_lstadd(&tab[E_ASSIGN]->lst, ft_lstnew(&tab[E_STRING], sizeof(t_graph **)));
	ft_lstadd(&tab[E_ASSIGN]->lst, ft_lstnew(&tab[E_EXP], sizeof(t_graph **)));
	ft_lstadd(&tab[E_ASSIGN]->lst, ft_lstnew(&tab[E_QUOTE], sizeof(t_graph **)));
	ft_lstadd(&tab[E_ASSIGN]->lst, ft_lstnew(&tab[E_DB_QUOTE], sizeof(t_graph **)));
}

void		set_semicolon_token(t_graph **tab)
{
	ft_lstadd(&tab[E_SEMICOLON]->lst, ft_lstnew(&tab[E_STRING], sizeof(t_graph **)));
	ft_lstadd(&tab[E_SEMICOLON]->lst, ft_lstnew(&tab[E_EXP], sizeof(t_graph **)));
	ft_lstadd(&tab[E_SEMICOLON]->lst, ft_lstnew(&tab[E_FORWARD], sizeof(t_graph **)));
	ft_lstadd(&tab[E_SEMICOLON]->lst, ft_lstnew(&tab[E_DGREAT], sizeof(t_graph **)));
	ft_lstadd(&tab[E_SEMICOLON]->lst, ft_lstnew(&tab[E_BACKWARD], sizeof(t_graph **)));
	ft_lstadd(&tab[E_SEMICOLON]->lst, ft_lstnew(&tab[E_DLESS], sizeof(t_graph **)));
	ft_lstadd(&tab[E_SEMICOLON]->lst, ft_lstnew(&tab[E_QUOTE], sizeof(t_graph **)));
	ft_lstadd(&tab[E_SEMICOLON]->lst, ft_lstnew(&tab[E_DB_QUOTE], sizeof(t_graph **)));
	ft_lstadd(&tab[E_SEMICOLON]->lst, ft_lstnew(&tab[E_SEMICOLON], sizeof(t_graph **)));
	ft_lstadd(&tab[E_SEMICOLON]->lst, ft_lstnew(&tab[E_IO_NUMBER], sizeof(t_graph **)));
	ft_lstadd(&tab[E_SEMICOLON]->lst, ft_lstnew(&tab[E_END], sizeof(t_graph **)));
}

void		set_pipe_token(t_graph **tab)
{
	ft_lstadd(&tab[E_PIPE]->lst, ft_lstnew(&tab[E_STRING], sizeof(t_graph **)));
	ft_lstadd(&tab[E_PIPE]->lst, ft_lstnew(&tab[E_EXP], sizeof(t_graph **)));
	ft_lstadd(&tab[E_PIPE]->lst, ft_lstnew(&tab[E_FORWARD], sizeof(t_graph **)));
	ft_lstadd(&tab[E_PIPE]->lst, ft_lstnew(&tab[E_DGREAT], sizeof(t_graph **)));
	ft_lstadd(&tab[E_PIPE]->lst, ft_lstnew(&tab[E_BACKWARD], sizeof(t_graph **)));
	ft_lstadd(&tab[E_PIPE]->lst, ft_lstnew(&tab[E_DLESS], sizeof(t_graph **)));
	ft_lstadd(&tab[E_PIPE]->lst, ft_lstnew(&tab[E_QUOTE], sizeof(t_graph **)));
	ft_lstadd(&tab[E_PIPE]->lst, ft_lstnew(&tab[E_DB_QUOTE], sizeof(t_graph **)));
	ft_lstadd(&tab[E_PIPE]->lst, ft_lstnew(&tab[E_IO_NUMBER], sizeof(t_graph **)));
	ft_lstadd(&tab[E_PIPE]->lst, ft_lstnew(&tab[E_ASSIGN], sizeof(t_graph **)));
}

void		set_ionumber_token(t_graph **tab)
{
	ft_lstadd(&tab[E_IO_NUMBER]->lst, ft_lstnew(&tab[E_FORWARD], sizeof(t_graph **)));
	ft_lstadd(&tab[E_IO_NUMBER]->lst, ft_lstnew(&tab[E_BACKWARD], sizeof(t_graph **)));
	ft_lstadd(&tab[E_IO_NUMBER]->lst, ft_lstnew(&tab[E_DGREAT], sizeof(t_graph **)));
	ft_lstadd(&tab[E_IO_NUMBER]->lst, ft_lstnew(&tab[E_DLESS], sizeof(t_graph **)));
}

/*
void		set_start_token(t_graph *start, t_graph **tab)
{
	start->end = 1;
	ft_lstadd(&start->lst, ft_lstnew(&tab[E_STRING], sizeof(t_graph **)));
	ft_lstadd(&start->lst, ft_lstnew(&tab[E_IF], sizeof(t_graph **)));
	ft_lstadd(&start->lst, ft_lstnew(&tab[E_QUOTE], sizeof(t_graph **)));
	ft_lstadd(&start->lst, ft_lstnew(&tab[E_DB_QUOTE], sizeof(t_graph **)));
}

void		set_string_token(t_graph **tab)
{
	tab[E_STRING]->end = 1;
	ft_lstadd(&tab[E_STRING]->lst, ft_lstnew(&tab[E_QUOTE], sizeof(t_graph **)));
	ft_lstadd(&tab[E_STRING]->lst, ft_lstnew(&tab[E_DB_QUOTE], sizeof(t_graph **)));
	ft_lstadd(&tab[E_STRING]->lst, ft_lstnew(&tab[E_STRING], sizeof(t_graph **)));
	ft_lstadd(&tab[E_STRING]->lst, ft_lstnew(&tab[E_IF], sizeof(t_graph **)));
	ft_lstadd(&tab[E_STRING]->lst, ft_lstnew(&tab[E_ELIF], sizeof(t_graph **)));
	ft_lstadd(&tab[E_STRING]->lst, ft_lstnew(&tab[E_ELSE], sizeof(t_graph **)));
	ft_lstadd(&tab[E_STRING]->lst, ft_lstnew(&tab[E_FI], sizeof(t_graph **)));
	ft_lstadd(&tab[E_STRING]->lst, ft_lstnew(&tab[E_BRACKET_CLOSE], sizeof(t_graph **)));
	ft_lstadd(&tab[E_STRING]->lst, ft_lstnew(&tab[E_PIPE], sizeof(t_graph **)));
}

void		set_quote_token(t_graph **tab)
{
	tab[E_QUOTE]->end = 1;
	ft_lstadd(&tab[E_QUOTE]->lst, ft_lstnew(&tab[E_QUOTE], sizeof(t_graph **)));
	ft_lstadd(&tab[E_QUOTE]->lst, ft_lstnew(&tab[E_DB_QUOTE], sizeof(t_graph **)));
	ft_lstadd(&tab[E_QUOTE]->lst, ft_lstnew(&tab[E_STRING], sizeof(t_graph **)));
	ft_lstadd(&tab[E_QUOTE]->lst, ft_lstnew(&tab[E_IF], sizeof(t_graph **)));
	ft_lstadd(&tab[E_QUOTE]->lst, ft_lstnew(&tab[E_ELIF], sizeof(t_graph **)));
	ft_lstadd(&tab[E_QUOTE]->lst, ft_lstnew(&tab[E_ELSE], sizeof(t_graph **)));
	ft_lstadd(&tab[E_QUOTE]->lst, ft_lstnew(&tab[E_FI], sizeof(t_graph **)));
	ft_lstadd(&tab[E_QUOTE]->lst, ft_lstnew(&tab[E_BRACKET_CLOSE], sizeof(t_graph **)));
	ft_lstadd(&tab[E_QUOTE]->lst, ft_lstnew(&tab[E_PIPE], sizeof(t_graph **)));
}

void		set_dbquote_token(t_graph **tab)
{
	tab[E_DB_QUOTE]->end = 1;
	ft_lstadd(&tab[E_DB_QUOTE]->lst, ft_lstnew(&tab[E_QUOTE], sizeof(t_graph **)));
	ft_lstadd(&tab[E_DB_QUOTE]->lst, ft_lstnew(&tab[E_DB_QUOTE], sizeof(t_graph **)));
	ft_lstadd(&tab[E_DB_QUOTE]->lst, ft_lstnew(&tab[E_STRING], sizeof(t_graph **)));
	ft_lstadd(&tab[E_DB_QUOTE]->lst, ft_lstnew(&tab[E_IF], sizeof(t_graph **)));
	ft_lstadd(&tab[E_DB_QUOTE]->lst, ft_lstnew(&tab[E_ELIF], sizeof(t_graph **)));
	ft_lstadd(&tab[E_DB_QUOTE]->lst, ft_lstnew(&tab[E_ELSE], sizeof(t_graph **)));
	ft_lstadd(&tab[E_DB_QUOTE]->lst, ft_lstnew(&tab[E_FI], sizeof(t_graph **)));
	ft_lstadd(&tab[E_DB_QUOTE]->lst, ft_lstnew(&tab[E_BRACKET_CLOSE], sizeof(t_graph **)));
	ft_lstadd(&tab[E_DB_QUOTE]->lst, ft_lstnew(&tab[E_PIPE], sizeof(t_graph **)));
}

void		set_pipe_token(t_graph **tab)
{
	tab[E_PIPE]->event = START_GRAPH;
	ft_lstadd(&tab[E_PIPE]->lst, ft_lstnew(&tab[E_STRING], sizeof(t_graph **)));
	ft_lstadd(&tab[E_PIPE]->lst, ft_lstnew(&tab[E_QUOTE], sizeof(t_graph **)));
	ft_lstadd(&tab[E_PIPE]->lst, ft_lstnew(&tab[E_DB_QUOTE], sizeof(t_graph **)));
}

void		set_if_token(t_graph **tab)
{
	enum e_type	type_end;

	tab[E_IF]->event = RECALL;

	type_end = E_THEN;
	ft_lstadd(&tab[E_IF]->type_end, ft_lstnew(&type_end, sizeof(enum e_type *)));

	ft_lstadd(&tab[E_IF]->lst, ft_lstnew(&tab[E_BRACKET_OPEN], sizeof(t_graph **)));
}

void		set_elif_token(t_graph **tab)
{
	enum e_type	type_end;
	enum e_type	type_parent;

	tab[E_ELIF]->event = RECALL;

	type_end = E_THEN;
	ft_lstadd(&tab[E_ELIF]->type_end, ft_lstnew(&type_end, sizeof(enum e_type *)));

	type_parent = E_IF;
	ft_lstadd(&tab[E_ELIF]->type_parent, ft_lstnew(&type_parent, sizeof(enum e_type *)));

	ft_lstadd(&tab[E_ELIF]->lst, ft_lstnew(&tab[E_BRACKET_OPEN], sizeof(t_graph **)));
}

void		set_else_token(t_graph **tab)
{
	enum e_type	type_end;
	enum e_type	type_parent;

	tab[E_ELSE]->event = RECALL;

	type_end = E_FI;
	ft_lstadd(&tab[E_ELSE]->type_end, ft_lstnew(&type_end, sizeof(enum e_type *)));

	type_parent = E_IF;
	ft_lstadd(&tab[E_ELSE]->type_parent, ft_lstnew(&type_parent, sizeof(enum e_type *)));

	ft_lstadd(&tab[E_ELSE]->lst, ft_lstnew(&tab[E_STRING], sizeof(t_graph **)));
	ft_lstadd(&tab[E_ELSE]->lst, ft_lstnew(&tab[E_QUOTE], sizeof(t_graph **)));
	ft_lstadd(&tab[E_ELSE]->lst, ft_lstnew(&tab[E_DB_QUOTE], sizeof(t_graph **)));
}

void		set_fi_token(t_graph **tab)
{
	tab[E_FI]->end = 1;
	tab[E_FI]->event = BACK;
	ft_lstadd(&tab[E_FI]->lst, ft_lstnew(&tab[E_STRING], sizeof(t_graph **)));
	ft_lstadd(&tab[E_FI]->lst, ft_lstnew(&tab[E_QUOTE], sizeof(t_graph **)));
	ft_lstadd(&tab[E_FI]->lst, ft_lstnew(&tab[E_DB_QUOTE], sizeof(t_graph **)));
	ft_lstadd(&tab[E_FI]->lst, ft_lstnew(&tab[E_FI], sizeof(t_graph **)));
	ft_lstadd(&tab[E_FI]->lst, ft_lstnew(&tab[E_IF], sizeof(t_graph **)));
}

void		set_then_token(t_graph **tab)
{
	enum e_type	type_end;
	enum e_type	type_parent;

	tab[E_THEN]->event = RECALL;

	type_end = E_FI;
	ft_lstadd(&tab[E_THEN]->type_end, ft_lstnew(&type_end, sizeof(enum e_type *)));
	type_end = E_ELIF;
	ft_lstadd(&tab[E_THEN]->type_end, ft_lstnew(&type_end, sizeof(enum e_type *)));
	type_end = E_ELSE;
	ft_lstadd(&tab[E_THEN]->type_end, ft_lstnew(&type_end, sizeof(enum e_type *)));

	type_parent = E_IF;
	ft_lstadd(&tab[E_THEN]->type_parent, ft_lstnew(&type_parent, sizeof(enum e_type *)));

	ft_lstadd(&tab[E_THEN]->lst, ft_lstnew(&tab[E_STRING], sizeof(t_graph **)));
	ft_lstadd(&tab[E_THEN]->lst, ft_lstnew(&tab[E_QUOTE], sizeof(t_graph **)));
	ft_lstadd(&tab[E_THEN]->lst, ft_lstnew(&tab[E_DB_QUOTE], sizeof(t_graph **)));
}

void		set_bracket_open_token(t_graph **tab)
{
	enum e_type	type_end;

	tab[E_BRACKET_OPEN]->event = RECALL;

	type_end = E_BRACKET_CLOSE;
	ft_lstadd(&tab[E_BRACKET_OPEN]->type_end, ft_lstnew(&type_end, sizeof(enum e_type *)));

	ft_lstadd(&tab[E_BRACKET_OPEN]->lst, ft_lstnew(&tab[E_STRING], sizeof(t_graph **)));
	ft_lstadd(&tab[E_BRACKET_OPEN]->lst, ft_lstnew(&tab[E_QUOTE], sizeof(t_graph **)));
	ft_lstadd(&tab[E_BRACKET_OPEN]->lst, ft_lstnew(&tab[E_DB_QUOTE], sizeof(t_graph **)));
}

void		set_bracket_close_token(t_graph **tab)
{
	tab[E_BRACKET_CLOSE]->event = BACK;
	ft_lstadd(&tab[E_BRACKET_CLOSE]->lst, ft_lstnew(&tab[E_THEN], sizeof(t_graph **)));
	ft_lstadd(&tab[E_BRACKET_CLOSE]->lst, ft_lstnew(&tab[E_BRACKET_OPEN], sizeof(t_graph **)));
}
*/
