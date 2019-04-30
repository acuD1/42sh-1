/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 14:23:48 by nrechati          #+#    #+#             */
/*   Updated: 2019/04/27 12:09:18 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

void			clear_node(void **data)
{
	t_node	*ptr;

	ptr = *data;
	free(ptr->var);
	free(ptr->data);
}

static void		free_anode(t_list *ptr)
{
	clear_node(&ptr->data);
	free(ptr->data);
}

static int8_t	del_node(t_list *ptr, char *var)
{
	t_list	*tmp;

	tmp = ptr;
	ptr = ptr->next;
	while (ptr != NULL)
	{
		if (ft_strequ(((t_node *)ptr->data)->var, var) == TRUE)
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

int8_t			free_node(t_list **alst, char *var)
{
	t_list	*ptr;
	t_node	*env;

	ptr = *alst;
	env = (t_node*)ptr->data;
	if (ft_strequ(env->var, var) == TRUE)
	{
		*alst = ptr->next;
		free_anode(ptr);
		free(ptr);
		return (SUCCESS);
	}
	return (del_node(ptr, var));
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
