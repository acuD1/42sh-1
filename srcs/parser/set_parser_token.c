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

void		set_start_token(t_graph *tab_tokens)
{
	static enum	e_type tab_good_type[] = {E_STRING, E_SPSTRING, E_DB_QUOTE,
				E_ASSIGN, E_GREAT, E_GREATAND, E_DGREAT, E_DGREATAND, E_LESS,
				E_LESSAND, E_DLESS, E_DLESSDASH, E_IO_NUMBER, E_END, E_ERROR};

	tab_tokens[E_START].good_type = tab_good_type;
	tab_tokens[E_SEMICOLON].good_type = tab_good_type;
}

void		set_word_token(t_graph *tab_tokens)
{
	static enum	e_type tab_good_type[] = {E_STRING, E_SPSTRING, E_DB_QUOTE,
				E_ASSIGN, E_GREAT, E_GREATAND, E_DGREAT, E_DGREATAND, E_LESS,
				E_LESSAND, E_DLESS,	E_DLESSDASH, E_IO_NUMBER, E_PIPE,
				E_SEMICOLON, E_END, E_ERROR};

	tab_tokens[E_STRING].good_type = tab_good_type;
	tab_tokens[E_SPSTRING].good_type = tab_good_type;
	tab_tokens[E_DB_QUOTE].good_type = tab_good_type;
	tab_tokens[E_GREATAND].good_type = tab_good_type;
	tab_tokens[E_DGREATAND].good_type = tab_good_type;
	tab_tokens[E_LESSAND].good_type = tab_good_type;
	tab_tokens[E_DLESSDASH].good_type = tab_good_type;
}
void		set_redirect_token(t_graph *tab_tokens)
{
	static enum	e_type tab_good_type[] = {E_STRING, E_SPSTRING, E_DB_QUOTE,
				E_IO_NUMBER, E_ERROR};

	tab_tokens[E_GREAT].good_type = tab_good_type;
	tab_tokens[E_DGREAT].good_type = tab_good_type;
	tab_tokens[E_LESS].good_type = tab_good_type;
	tab_tokens[E_DLESS].good_type = tab_good_type;
}

void		set_assign_token(t_graph *tab_tokens)
{
	static enum	e_type tab_good_type[] = {E_STRING, E_SPSTRING, E_DB_QUOTE,
				E_ERROR};

	tab_tokens[E_ASSIGN].good_type = tab_good_type;
}

void		set_pipe_token(t_graph *tab_tokens)
{
	static enum	e_type tab_good_type[] = {E_STRING, E_SPSTRING, E_DB_QUOTE,
				E_ASSIGN, E_GREAT, E_GREATAND, E_DGREAT, E_DGREATAND, E_LESS,
				E_LESSAND, E_DLESS, E_DLESSDASH, E_IO_NUMBER, E_ERROR};

	tab_tokens[E_PIPE].good_type = tab_good_type;
}

void		set_ionumber_token(t_graph *tab_tokens)
{
	static enum	e_type tab_good_type[] = {E_GREAT, E_GREATAND, E_DGREAT,
				E_DGREATAND, E_LESS, E_LESSAND, E_DLESS, E_DLESSDASH, E_END,
				E_ERROR};

	tab_tokens[E_IO_NUMBER].good_type = tab_good_type;
}
