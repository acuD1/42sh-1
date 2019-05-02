/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 14:23:48 by nrechati          #+#    #+#             */
/*   Updated: 2019/04/30 20:56:30 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"

void			clear_node(void **data)
{
	t_variable	*ptr;

	ptr = *data;
	free(ptr->name);
	free(ptr->data);
}

static void		free_anode(t_list *ptr)
{
	clear_node(&ptr->data);
	free(ptr->data);
}

static int8_t	del_node(t_list *ptr, const char *name)
{
	t_list	*tmp;

	tmp = ptr;
	ptr = ptr->next;
	while (ptr != NULL)
	{
		if (ft_strequ(((t_variable *)ptr->data)->name, name) == TRUE)
		{
			tmp->next = ptr->next;
			free_anode(ptr);
			free(ptr);
			return (SUCCESS);
		}
		tmp = tmp->next;
		ptr = ptr->next;
	}
	return (FAILURE);
}

int8_t			free_node(t_list **alst, const char *name)
{
	t_list		*ptr;
	t_variable	*env;

	ptr = *alst;
	env = (t_variable*)ptr->data;
	if (ft_strequ(env->name, name) == TRUE)
	{
		*alst = ptr->next;
		free_anode(ptr);
		free(ptr);
		return (SUCCESS);
	}
	return (del_node(ptr, name));
}

int8_t			free_lst(t_list **alst)
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
	*alst = NULL;
	return (SUCCESS);
}
