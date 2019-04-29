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

void			generate_graph(t_registry *shell)
{
	set_graph(shell->graph);
}
