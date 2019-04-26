/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 14:06:50 by nrechati          #+#    #+#             */
/*   Updated: 2019/04/26 19:18:31 by ffoissey         ###   ########.fr       */
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
		ft_printf("%s=%s\n", ((t_node *)ptr->data)->var
				, ((t_node *)ptr->data)->data, ptr->next);
		ptr = ptr->next;
	}
}

int				f_create_node(t_list **alst, char *str)
{
	t_node	s_node;
	t_list	*newdir;

	if (str == NULL)
		return (0);
	ft_bzero(&s_node, sizeof(t_node));
	s_node.var = ft_strsub(str, 0, ft_strcspn(str, "="));
	s_node.data = ft_strdup(str + (ft_strcspn(str, "=") + 1));
	if (s_node.var == NULL || s_node.data == NULL)
		return (0);
	if (!(newdir = ft_lstnew(&s_node, sizeof(t_node))))
		return (0);
	ft_lstaddback(alst, newdir);
	return (1);
}

int				s_create_node(t_list **alst, char *var, char *data)
{
	t_node s_node;
	t_list *newdir;

	if (var == NULL)
		return (0);
	ft_bzero(&s_node, sizeof(t_node));
	s_node.var = ft_strdup(var);
	s_node.data = ft_strdup(data);
	if (s_node.var == NULL || s_node.data == NULL)
		return (0);
	if (!(newdir = ft_lstnew(&s_node, sizeof(t_node))))
		return (0);
	ft_lstaddback(alst, newdir);
	return (1);
}

int				change_node(t_list **alst, char *var, char *data)
{
	t_list *ptr;

	ptr = *alst;
	if (var == NULL || data == NULL)
		return (0);
	while (ptr != NULL)
	{
		if (!ft_strcmp(((t_node *)ptr->data)->var, var))
		{
			free(((t_node *)ptr->data)->data);
			((t_node *)ptr->data)->data = data;
			return (1);
		}
		ptr = ptr->next;
	}
	if (!s_create_node(alst, var, data))
		return (0);
	return (1);
}

int				search_data(t_list **alst, char *var)
{
	t_list *ptr;

	ptr = *alst;
	while (ptr != NULL)
	{
		if (!ft_strcmp(((t_node *)ptr->data)->var, var))
			return (1);
		ptr = ptr->next;
	}
	return (0);
}

char			*get_data(t_list **alst, char *var)
{
	t_list *ptr;

	ptr = *alst;
	while (ptr != NULL)
	{
		if (!ft_strcmp(((t_node *)ptr->data)->var, var))
			return (((t_node *)ptr->data)->data);
		ptr = ptr->next;
	}
	return (NULL);
}
