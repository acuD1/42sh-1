/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 14:23:48 by nrechati          #+#    #+#             */
/*   Updated: 2019/04/19 23:53:46 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

void	clear_node(void **data)
{
	t_variable	*ptr;

	ptr = *data;
	free(ptr->name);
	free(ptr->data);
}

int		free_anode(t_list *ptr)
{
	clear_node(&ptr->data);
	free(ptr->data);
	return (1);
}

int		del_node(t_list *ptr, char *name)
{
	t_list	*tmp;

	tmp = ptr;
	ptr = ptr->next;
	while (ptr != NULL)
	{
		if (!ft_strcmp(((t_variable *)ptr->data)->name, name))
		{
			tmp->next = ptr->next;
			free_anode(ptr);
			free(ptr);
			return (1);
		}
		tmp = tmp->next;
		ptr = ptr->next;
	}
	return (0);
}

int		free_node(t_list **alst, char *name)
{
	t_list	*ptr;
	t_variable	*env;

	ptr = *alst;
	env = (t_variable*)ptr->data;
	if (!ft_strcmp(env->name, name))
	{
		*alst = ptr->next;
		free_anode(ptr);
		free(ptr);
		return (1);
	}
	if (del_node(ptr, name))
		return (1);
	return (0);
}

int		free_lst(t_list **alst)
{
	t_list	*ptr;
	t_list	*tmp;

	tmp = NULL;
	ptr = *alst;
	while (ptr != NULL)
	{
		free_anode(ptr);
		tmp = ptr;
		ptr = ptr->next;
		free(tmp);
	}
	return (1);
}
