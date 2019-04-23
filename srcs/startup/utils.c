/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 14:06:50 by nrechati          #+#    #+#             */
/*   Updated: 2019/04/23 21:16:56 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"


int				s_create_node(t_list **alst, char *name, char *data)
{
	t_variable variable;
	t_list *newdir;

	if (name == NULL)
		return (0);
	ft_bzero(&variable, sizeof(t_variable));
	variable.name = ft_strdup(name);
	variable.data = ft_strdup(data);
	if (variable.name == NULL || variable.data == NULL)
		return (0);
	if (!(newdir = ft_lstnew(&variable, sizeof(t_variable))))
		return (0);
	ft_lstaddback(alst, newdir);
	return (1);
}


int				find_data(void *searched, void *to_find)
{
	t_variable *tmp;

	tmp = searched;
	return (ft_strequ(tmp->data, (char *)to_find));
}

char			*get_data(t_list *lst, char *name)
{
	while (lst != NULL)
	{
		if (ft_strequ(((t_variable *)lst->data)->name, name))
			return (((t_variable *)lst->data)->data);
		lst = lst->next;
	}
	return (NULL);
}
int				change_node(t_list **alst, char *name, char *data)
{
	t_list *ptr;

	if (name == NULL || data == NULL)
		return (0);
	if ((ptr = ft_lstfind(*alst, name, find_data)))
	{
		ft_strdel(&((t_variable *)ptr->data)->data);
		((t_variable *)ptr->data)->data = data;
		return (1);
	}
	if (!s_create_node(alst, name, data))
		return (0);
	return (1);
}
