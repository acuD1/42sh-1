/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_graph.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 16:42:01 by ffoissey          #+#    #+#             */
/*   Updated: 2019/04/24 16:42:04 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void		set_graph(t_graph *tab_tokens)
{
	set_start_token(tab_tokens);
	set_word_token(tab_tokens);
	set_redirect_token(tab_tokens);
	set_assign_token(tab_tokens);
	set_semicolon_token(tab_tokens);
	set_pipe_token(tab_tokens);
	set_ionumber_token(tab_tokens);
}

t_graph			*generate_graph(void)
{
	static t_graph		tab_tokens[NB_OF_TOKENS];
	int					i;

	//////////// bzero general;
	i = 0;
	while (i < NB_OF_TOKENS)
		ft_bzero(&tab_tokens[i++], sizeof(t_graph));
	set_graph(tab_tokens);
	return (tab_tokens);
}
