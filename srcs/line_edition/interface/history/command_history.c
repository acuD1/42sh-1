/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_history.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 13:44:00 by skuppers          #+#    #+#             */
/*   Updated: 2019/03/07 11:23:15 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#include "line_edit.h"
#include "history.h"
#include "libft.h"
#include "log.h"
/*
t_history	*create_history_entry(char	*entry)
{
	char		*cmd;
	t_history	*new;

	if (!(new = malloc(sizeof(t_history))))
		return (NULL);
	ft_memset(new, 0, sizeof(t_history));
	new->next = NULL;
	new->prev = NULL;
	if ((cmd = ft_strdup(entry)) == NULL)
	{
		free(new);
		return (NULL);
	}
	new->command = cmd;
	return (new);
}

void	push_history_entry(t_history **head, t_history *new)
{
	(*head)->next = new;
	new->prev = *head;
	*head = new;
}
*/
