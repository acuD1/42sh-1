#include "parser.h"

void		set_start_token(t_graph *start, t_graph **tab)
{
	ft_lstadd(&start->lst, ft_lstnew(&tab[E_STRING], sizeof(t_graph **)));
}

void		set_string_token(t_graph *start, t_graph **tab)
{
	(void)start;
	ft_lstadd(&tab[E_STRING]->lst, ft_lstnew(&tab[E_STRING], sizeof(t_graph **)));
	ft_lstadd(&tab[E_STRING]->lst, ft_lstnew(&tab[E_IF], sizeof(t_graph **)));
	ft_lstadd(&tab[E_STRING]->lst, ft_lstnew(&tab[E_ELIF], sizeof(t_graph **)));
	ft_lstadd(&tab[E_STRING]->lst, ft_lstnew(&tab[E_ELSE], sizeof(t_graph **)));
	ft_lstadd(&tab[E_STRING]->lst, ft_lstnew(&tab[E_FI], sizeof(t_graph **)));
	ft_lstadd(&tab[E_STRING]->lst, ft_lstnew(&tab[E_BRACKET_CLOSE], sizeof(t_graph **)));
}

void		set_if_token(t_graph *start, t_graph **tab)
{
	enum e_type	type_end;

	(void)start;
	tab[E_IF]->event = RECALL;

	type_end = E_FI;
	ft_lstadd(&tab[E_IF]->type_end, ft_lstnew(&type_end, sizeof(enum e_type *)));
	type_end = E_ELIF;
	ft_lstadd(&tab[E_IF]->type_end, ft_lstnew(&type_end, sizeof(enum e_type *)));
	type_end = E_ELSE;
	ft_lstadd(&tab[E_IF]->type_end, ft_lstnew(&type_end, sizeof(enum e_type *)));

	ft_lstadd(&tab[E_IF]->lst, ft_lstnew(&tab[E_BRACKET_OPEN], sizeof(t_graph **)));
}

void		set_elif_token(t_graph *start, t_graph **tab)
{
	enum e_type	type_end;
	enum e_type	type_parent;

	(void)start;
	tab[E_IF]->event = RECALL;

	type_end = E_FI;
	ft_lstadd(&tab[E_ELIF]->type_end, ft_lstnew(&type_end, sizeof(enum e_type *)));
	type_end = E_ELIF;
	ft_lstadd(&tab[E_IF]->type_end, ft_lstnew(&type_end, sizeof(enum e_type *)));
	type_end = E_ELSE;
	ft_lstadd(&tab[E_ELIF]->type_end, ft_lstnew(&type_end, sizeof(enum e_type *)));

	type_parent = E_IF;
	ft_lstadd(&tab[E_ELIF]->type_parent, ft_lstnew(&type_parent, sizeof(enum e_type *)));

	ft_lstadd(&tab[E_ELIF]->lst, ft_lstnew(&tab[E_BRACKET_OPEN], sizeof(t_graph **)));
}

void		set_else_token(t_graph *start, t_graph **tab)
{
	enum e_type	type_end;
	enum e_type	type_parent;

	(void)start;
	tab[E_ELSE]->event = RECALL;

	type_end = E_FI;
	ft_lstadd(&tab[E_ELSE]->type_end, ft_lstnew(&type_end, sizeof(enum e_type *)));

	type_parent = E_IF;
	ft_lstadd(&tab[E_ELSE]->type_parent, ft_lstnew(&type_parent, sizeof(enum e_type *)));

	ft_lstadd(&tab[E_ELSE]->lst, ft_lstnew(&tab[E_STRING], sizeof(t_graph **)));
}

void		set_fi_token(t_graph *start, t_graph **tab)
{
	(void)start;
	tab[E_FI]->event = BACK;
	ft_lstadd(&tab[E_FI]->lst, ft_lstnew(&tab[E_STRING], sizeof(t_graph **)));
	ft_lstadd(&tab[E_FI]->lst, ft_lstnew(&tab[E_FI], sizeof(t_graph **)));
	ft_lstadd(&tab[E_FI]->lst, ft_lstnew(&tab[E_IF], sizeof(t_graph **)));
}

void		set_bracket_open_token(t_graph *start, t_graph **tab)
{
	enum e_type	type_end;

	(void)start;
	tab[E_BRACKET_OPEN]->event = RECALL;

	type_end = E_BRACKET_CLOSE;
	ft_lstadd(&tab[E_BRACKET_OPEN]->type_end, ft_lstnew(&type_end, sizeof(enum e_type *)));

	ft_lstadd(&tab[E_BRACKET_OPEN]->lst, ft_lstnew(&tab[E_STRING], sizeof(t_graph **)));
}

void		set_bracket_close_token(t_graph *start, t_graph **tab)
{
	(void)start;
	tab[E_BRACKET_CLOSE]->event = BACK;
	ft_lstadd(&tab[E_BRACKET_CLOSE]->lst, ft_lstnew(&tab[E_STRING], sizeof(t_graph **)));
	ft_lstadd(&tab[E_BRACKET_CLOSE]->lst, ft_lstnew(&tab[E_IF], sizeof(t_graph **)));
	ft_lstadd(&tab[E_BRACKET_CLOSE]->lst, ft_lstnew(&tab[E_BRACKET_OPEN], sizeof(t_graph **)));
}

