/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   foobar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 09:42:16 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/26 12:01:15 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#include "history.h"


char		*apply_history_filter(char *command)
{
	char	*ptr;
	char	*new;

	new = ft_strdup(command);
	ptr = new;
	while (*ptr)
	{
		if (*ptr == IFS_CHAR)
			*ptr = ' ';
		++ptr;
	}
	return (new);
}

void		push_history_entry(t_history **head, t_history *node)
{
	t_history *hist_ptr;

	if (head == NULL || *head == NULL)
		*head = node;
	else
	{
		hist_ptr = *head;
		while (hist_ptr->prev)
			hist_ptr = hist_ptr->prev;
		hist_ptr->prev = node;
		node->next = hist_ptr;
		*head = node;
	}
}

t_history	*create_history_entry(char *command)
{
	char		*dup;
	t_history	*new;

	new = NULL;
	dup = apply_history_filter(command);
	new = malloc(sizeof(t_history));
	new->command = dup;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}
