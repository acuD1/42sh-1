/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_parser.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 14:32:32 by skuppers          #+#    #+#             */
/*   Updated: 2019/03/02 11:13:29 by skuppers         ###   ########.fr       */
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
/*
int							delete_env_node(t_environment_node *head, char *key)
{
	(void)head;
	(void)key;
	return (0);
}

int							overwrite_env_value(t_environment_node *head,
		char *key, char *new_value)
{
	t_environment_node	*ptr;

	ptr = head;
	while (ptr->next != NULL)
	{
		if (ft_strequ(ptr->key, key))
		{
			ft_strdel(&(ptr->value));
			ptr->value = ft_strdup(new_value);
			return (0);
		}
		ptr = ptr->next;
	}
	return (-1);
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
*/
/*
 *	Returns the head from linked list with the entire environment.
 *	With the syntax: key = value.
 */

t_environment_node	*parse_environment(char **environment)
{
	(void)environment;
	/*
	t_environment_node		*head;
	t_environment_node		*new;
	unsigned int			separator;

	//TODO: add internal nodes (SHLVL, etc...)

	head = NULL;
	if (environment == NULL)
	{
		//handle NULL environment
	}
	else
	{
		while (*environment)
		{
			separator = ft_(*environment, ENV_SEPARATOR);
			new = create_env_node(ft_strsub(*environment, 0, separator),
					ft_strsub(*environment, separator + 1,
						ft_strlen(*environment) - (separator + 1)));
			if (new == NULL)
				continue ;
			if (head == NULL)
				head = new;
			else
				ft_listappend(head, new);
			++environment;
		}
	}*/
	return (NULL);
}
