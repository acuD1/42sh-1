/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 14:23:48 by nrechati          #+#    #+#             */
/*   Updated: 2019/04/02 14:09:25 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

void	clear_node(void **data)
{
	t_node	*ptr;

	ptr = *data;
	free(ptr->var);
	free(ptr->data);
}

int		free_anode(t_list *ptr)
{
	clear_node(&ptr->data);
	free(ptr->data);
	return (1);
}

int		del_node(t_list *ptr, char *var)
{
	t_list	*tmp;

	tmp = ptr;
	ptr = ptr->next;
	while (ptr != NULL)
	{
		if (!ft_strcmp(((t_node *)ptr->data)->var, var))
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

int		free_node(t_list **alst, char *var)
{
	t_list	*ptr;
	t_node	*env;

	ptr = *alst;
	env = (t_node*)ptr->data;
	if (!ft_strcmp(env->var, var))
	{
		*alst = ptr->next;
		free_anode(ptr);
		free(ptr);
		return (1);
	}
	if (del_node(ptr, var))
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
