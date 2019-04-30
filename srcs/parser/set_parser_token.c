/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_parser_token.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 16:42:24 by ffoissey          #+#    #+#             */
/*   Updated: 2019/05/01 01:18:01 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	set_graph_node(t_graph *node, enum e_type type, int nb_of_good_type,
							enum e_type *tab_good_type)
{
	node[type].nb_of_good_type = nb_of_good_type;
	node[type].good_type = tab_good_type;
}

void		set_start_token(t_graph *tab_tokens)
{
	static enum	e_type tab_good_type[14] = {ALL, AND_REDIRECT, E_END, E_ASSIGN};
	int			nb_of_good_type;

	nb_of_good_type = 14;
	set_graph_node(tab_tokens, E_START, nb_of_good_type, tab_good_type);
	set_graph_node(tab_tokens, E_SEMICOLON, nb_of_good_type, tab_good_type);
}

void		set_word_token(t_graph *tab_tokens)
{
	static enum e_type tab_good_type[16] = {ALL_END, E_ASSIGN, AND_REDIRECT, PIPELINE};
	int			nb_of_good_type;

	nb_of_good_type = 16;
	set_graph_node(tab_tokens, E_STRING, nb_of_good_type, tab_good_type);
	set_graph_node(tab_tokens, E_DB_QUOTE, nb_of_good_type, tab_good_type);
}
void		set_redirect_token(t_graph *tab_tokens)
{
	static enum e_type tab_good_type[6] = {WORD, IO};
	int			nb_of_good_type;

	nb_of_good_type = 6;
	set_graph_node(tab_tokens, E_GREAT, nb_of_good_type, tab_good_type);
	set_graph_node(tab_tokens, E_LESS, nb_of_good_type, tab_good_type);
	set_graph_node(tab_tokens, E_DGREAT, nb_of_good_type, tab_good_type);
	set_graph_node(tab_tokens, E_DLESS, nb_of_good_type, tab_good_type);
	set_graph_node(tab_tokens, E_GREATAND, nb_of_good_type, tab_good_type);
	set_graph_node(tab_tokens, E_LESSAND, nb_of_good_type, tab_good_type);
}

void		set_assign_token(t_graph *tab_tokens)
{
	static enum e_type tab_good_type[5] = {WORD};
	int			nb_of_good_type;

	nb_of_good_type = 5;
	set_graph_node(tab_tokens, E_ASSIGN, nb_of_good_type, tab_good_type);
}

void		set_pipe_token(t_graph *tab_tokens)
{
	static enum e_type tab_good_type[11] = {ALL, E_ASSIGN};
	int			nb_of_good_type;

	nb_of_good_type = 11;
	set_graph_node(tab_tokens, E_PIPE, nb_of_good_type, tab_good_type);
}

void		set_ionumber_token(t_graph *tab_tokens)
{
	static enum e_type tab_good_type[7] = {REDIRECT, E_END};
	int			nb_of_good_type;

	nb_of_good_type = 7;
	set_graph_node(tab_tokens, E_IO_NUMBER, nb_of_good_type, tab_good_type);
}
