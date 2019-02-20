/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_parser.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 14:32:32 by skuppers          #+#    #+#             */
/*   Updated: 2019/02/20 15:12:49 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "startup.h"

char			*get_env_node_value(t_environment_node *head, char *key)
{
	t_environment_node *ptr;

	ptr = head;
	while (ptr->next != NULL)
	{
		if (ft_strequ(ptr->key, key))
			return (ptr->value);
		ptr = ptr->next;
	}
	return (NULL);
}

int							delete_env_node(t_environment_node *head, char *key)
{

}

int							overwrite_env_value(t_environment_node *head,
		char *key, char *new_value)
{

}

static t_environment_node	*create_env_node(char *key, char *value)
{
	t_environment_node *new;

	if (!(new = malloc(sizeof(t_environment_node))))
	{
		ft_strdel(&key);
		ft_strdel(&value);
		return (NULL);
	}
	new->key = key;
	new->value = value;
	new->next = NULL;
	return (new);
}

static void				ft_listappend(t_environment_node *head,
		t_environment_node *new)
{
	t_environment_node tmp;

	tmp = head;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
}

/*
 *	Returns the head from linked list with the entire environment.
 *	With the syntax: key = value.
 */
t_environment_node	*parse_environment(char **environment)
{
	/* TODO:
	 *	check for environment
	 *	and if it is not present
	 *	check for /etc/paths.d/
	 *	and /etc/manpaths
	 *
	 *	Add essential values if their not present
	 */

	t_environment_node		*head;
	t_environment_node		*new;
	unsigned int			separator;

	if (environment == NULL)
	{
		//check /etc/paths.d
		//		/etc/manpaths.d
		//add internal nodes (SHLVL, PWD, _, etc...)
	}
	else
	{
		while (*environment)
		{
			separator = ft_strnchr(*environment, '=');
			new = create_environment_node(ft_strsub(*environment, 0, separator),
					ft_strsub(*environment, separator + 1,
						ft_strlen(*environment) - (i + 1)));
			if (new == NULL)
				continue ;
			if (head == NULL)
				head = new;
			else
				ft_listappend(head, new);
			++environment;
		}
	}
	return (head);
}
