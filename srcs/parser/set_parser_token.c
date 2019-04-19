#include "parser.h"

void		set_start_token(t_graph *start, t_graph **tab)
{
	static enum e_type ty[12] = {ALL_END, E_ASSIGN};
	int		i;

	i = 0;
	while (i < 12)
	{
		ft_lstadd(&start->lst, ft_lstnew(&tab[ty[i]], sizeof(tab)));
		i++;
	}
}

void		set_word_token(t_graph **tab)
{
	static enum e_type ty[13] = {ALL_END, E_ASSIGN, PIPELINE};
	int		i;

	i = 0;
	while (i < 13)
	{
		ft_lstadd(&tab[E_STRING]->lst, ft_lstnew(&tab[ty[i]], sizeof(tab)));
		ft_lstadd(&tab[E_EXP]->lst, ft_lstnew(&tab[ty[i]], sizeof(tab)));
		ft_lstadd(&tab[E_QUOTE]->lst, ft_lstnew(&tab[ty[i]], sizeof(tab)));
		ft_lstadd(&tab[E_DB_QUOTE]->lst, ft_lstnew(&tab[ty[i]], sizeof(tab)));
		i++;
	}
}

void		set_redirect_token(t_graph **tab)
{
	static enum e_type ty[5] = {WORD, IO};
	int		i;

	i = 0;
	while (i < 5)
	{
		ft_lstadd(&tab[E_GREAT]->lst, ft_lstnew(&tab[ty[i]], sizeof(tab)));
		ft_lstadd(&tab[E_LESS]->lst, ft_lstnew(&tab[ty[i]], sizeof(tab)));
		ft_lstadd(&tab[E_DGREAT]->lst, ft_lstnew(&tab[ty[i]], sizeof(tab)));
		ft_lstadd(&tab[E_DLESS]->lst, ft_lstnew(&tab[ty[i]], sizeof(tab)));
		ft_lstadd(&tab[E_GREATAND]->lst, ft_lstnew(&tab[ty[i]], sizeof(tab)));
		ft_lstadd(&tab[E_LESSAND]->lst, ft_lstnew(&tab[ty[i]], sizeof(tab)));
		i++;
	}
}

void		set_assign_token(t_graph **tab)
{
	static enum e_type ty[4] = {WORD};
	int		i;

	i = 0;
	while (i < 4)
	{
		ft_lstadd(&tab[E_ASSIGN]->lst, ft_lstnew(&tab[ty[i]], sizeof(tab)));
		i++;
	}
}

void		set_semicolon_token(t_graph **tab)
{
	static enum e_type ty[11] = {ALL, E_END, E_ASSIGN};
	int		i;

	i = 0;
	while (i < 11)
	{
		ft_lstadd(&tab[E_SEMICOLON]->lst, ft_lstnew(&tab[ty[i]], sizeof(tab)));
		i++;
	}
}

void		set_pipe_token(t_graph **tab)
{
	static enum e_type ty[10] = {ALL, E_ASSIGN};
	int		i;

	i = 0;
	while (i < 10)
	{
		ft_lstadd(&tab[E_PIPE]->lst, ft_lstnew(&tab[ty[i]], sizeof(tab)));
		i++;
	}
}

void		set_ionumber_token(t_graph **tab)
{
	static enum e_type ty[7] = {REDIRECT, E_END};
	int		i;

	i = 0;
	while (i < 7)
	{
		ft_lstadd(&tab[E_IO_NUMBER]->lst, ft_lstnew(&tab[ty[i]], sizeof(tab)));
		i++;
	}
}

/*
void		set_pipe_token(t_graph **tab)
{
	tab[E_PIPE]->event = START_GRAPH;
}

void		set_if_token(t_graph **tab)
{
	enum e_type	type_end;

	tab[E_IF]->event = RECALL;

	type_end = E_THEN;
	ft_lstadd(&tab[E_IF]->type_end, ft_lstnew(&type_end, sizeof(enum e_type *)));

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

}

void		set_fi_token(t_graph **tab)
{
	tab[E_FI]->event = BACK;
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

}

void		set_bracket_open_token(t_graph **tab)
{
	enum e_type	type_end;

	tab[E_BRACKET_OPEN]->event = RECALL;

	type_end = E_BRACKET_CLOSE;
	ft_lstadd(&tab[E_BRACKET_OPEN]->type_end, ft_lstnew(&type_end, sizeof(enum e_type *)));

}

void		set_bracket_close_token(t_graph **tab)
{
	tab[E_BRACKET_CLOSE]->event = BACK;
	ft_lstadd(&tab[E_BRACKET_CLOSE]->lst, ft_lstnew(&tab[E_THEN], sizeof(t_graph **)));
}
*/
