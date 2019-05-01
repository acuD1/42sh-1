/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_graph.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 16:42:01 by ffoissey          #+#    #+#             */
/*   Updated: 2019/04/30 16:14:34 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void			generate_graph(t_registry *shell)
{
	set_start_token(shell->graph);
	set_word_token(shell->graph);
	set_redirect_token(shell->graph);
	set_and_redirect_token(shell->graph);
	set_assign_token(shell->graph);
	set_pipe_token(shell->graph);
	set_ionumber_token(shell->graph);
}
