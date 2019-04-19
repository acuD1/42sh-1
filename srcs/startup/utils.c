/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 14:06:50 by nrechati          #+#    #+#             */
/*   Updated: 2019/04/20 00:03:01 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

void			print_lst(t_list **alst)
{
	t_list *ptr;

	if (!alst)
		return ;
	ptr = *alst;
	while (ptr != NULL)
	{
		ft_printf("%s=%s\n", ((t_variable *)ptr->data)->name
					, ((t_variable *)ptr->data)->data);
		ptr = ptr->next;
	}
}

int				f_create_node(t_list **alst, char *str)
{
	t_variable	variable;
	t_list		*newdir;

	if (str == NULL)
		return (0);
	variable.name = ft_strsub(str, 0, ft_strcspn(str, "="));
	variable.data = ft_strdup(str + (ft_strcspn(str, "=") + 1));
	if (variable.name == NULL || variable.data == NULL)
		return (0);
	if (!(newdir = ft_lstnew(&variable, sizeof(t_variable))))
		return (0);
	ft_lstaddback(alst, newdir);
	return (1);
}

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

int				change_node(t_list **alst, char *name, char *data)
{
	t_list *ptr;

	ptr = *alst;
	if (name == NULL || data == NULL)
		return (0);
	while (ptr != NULL)
	{
		if (!ft_strcmp(((t_variable *)ptr->data)->name, name))
		{
			free(((t_variable *)ptr->data)->data);
			((t_variable *)ptr->data)->data = data;
			return (1);
		}
		ptr = ptr->next;
	}
	if (!s_create_node(alst, name, data))
		return (0);
	return (1);
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
