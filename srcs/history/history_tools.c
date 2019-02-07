/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 16:06:10 by skuppers          #+#    #+#             */
/*   Updated: 2019/01/09 10:25:07 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"
#include "log.h"
#include <stdlib.h>
#include "libft.h"


t_history	*create_history_entry(char *command)
{
	t_history	*new_entry;
	char		*new_command;

	if ((new_entry = malloc(sizeof(t_history))) == NULL)
	{
		log_print(LOG_ERROR, "Could not allocate memory for history entry.\n");
		return (NULL);
	}
	if ((new_command = ft_strdup(command)) == NULL)
	{
		log_print(LOG_ERROR, "Could not allocate memory for historycontent.\n");
		free(new_entry);
		return (NULL);
	}
	//TODO: Handle ID
	//new_entry->ID = X
	new_entry->command = new_command;
	new_entry->next = NULL;
	new_entry->prev = NULL;
	return (new_entry);
}

void		push_history_entry(t_history **head, t_history *node)
{
	if (*head != NULL)
	{
		node->next = *head;
		(*head)->prev = node;
	}
	*head = node;
}

t_history	*get_history_entry()
{
	//
	return (NULL);
}
/*
int			write_history_to_file(t_history *last)
{
	return (0);
}

t_history	*load_history_from_file(void)
{
	return (NULL);
}*/
