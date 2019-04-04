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
	ft_lstadd(&tab[E_STRING]->lst, ft_lstnew(&tab[E_FI], sizeof(t_graph **)));
}

void		set_if_token(t_graph *start, t_graph **tab)
{
	(void)start;
	tab[E_IF]->event = RECALL;
	tab[E_IF]->type_end = E_FI;
	ft_lstadd(&tab[E_IF]->lst, ft_lstnew(&tab[E_BRACKET_OPEN], sizeof(t_graph **)));
}

void		set_fi_token(t_graph *start, t_graph **tab)
{
	(void)start;
	ft_lstadd(&tab[E_FI]->lst, ft_lstnew(&tab[E_STRING], sizeof(t_graph **)));
	ft_lstadd(&tab[E_FI]->lst, ft_lstnew(&tab[E_FI], sizeof(t_graph **)));
	ft_lstadd(&tab[E_FI]->lst, ft_lstnew(&tab[E_IF], sizeof(t_graph **)));
}

void		set_bracket_open_token(t_graph *start, t_graph **tab)
{
	(void)start;
	tab[E_BRACKET_OPEN]->event = RECALL;
	tab[E_BRACKET_OPEN]->type_end = E_BRACKET_CLOSE;
	ft_lstadd(&tab[E_BRACKET_OPEN]->lst, ft_lstnew(&tab[E_STRING], sizeof(t_graph **)));
}

void		set_bracket_close_token(t_graph *start, t_graph **tab)
{
	(void)start;
	ft_lstadd(&tab[E_BRACKET_CLOSE]->lst, ft_lstnew(&tab[E_STRING], sizeof(t_graph **)));
	ft_lstadd(&tab[E_BRACKET_CLOSE]->lst, ft_lstnew(&tab[E_IF], sizeof(t_graph **)));
	ft_lstadd(&tab[E_BRACKET_CLOSE]->lst, ft_lstnew(&tab[E_BRACKET_OPEN], sizeof(t_graph **)));
}

