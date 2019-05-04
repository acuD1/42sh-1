/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp_display.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 16:13:18 by cempassi          #+#    #+#             */
/*   Updated: 2019/05/04 16:04:09 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"

t_registry	*g_shell;

void		print_token(t_list *list)
{
	t_token *token;
	token = list->data;

	ft_printf("type_id = [ %2d ] | type_name = [ %5s ] | data = [ %s ]\n",
				token->type, g_shell->grammar[token->type], token->data);
}
