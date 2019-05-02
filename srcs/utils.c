/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 14:06:50 by nrechati          #+#    #+#             */
/*   Updated: 2019/04/30 20:59:23 by cempassi         ###   ########.fr       */
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
				, ((t_variable *)ptr->data)->data, ptr->next);
		ptr = ptr->next;
	}
}

int8_t			f_create_node(t_list **alst, char *str)
{
	t_variable	variable;
	t_list	*newdir;

	if (str == NULL)
		return (FAILURE);
	ft_bzero(&variable, sizeof(t_variable));
	variable.name = ft_strsub(str, 0, ft_strcspn(str, "="));
	variable.data = ft_strdup(str + (ft_strcspn(str, "=") + 1));
	if (variable.name == NULL || variable.data == NULL)
		return (FAILURE);
	if ((newdir = ft_lstnew(&s_node, sizeof(t_node))) == NULL)
		return (FAILURE);
	ft_lstaddback(alst, newdir);
	return (SUCCESS);
}

int8_t			s_create_node(t_list **alst, char *var, char *data)
{
	t_variable variable;
	t_list *newdir;

	if (var == NULL)
		return (FAILURE);
	ft_bzero(&s_node, sizeof(t_node));
	s_node.var = ft_strdup(var);
	s_node.data = ft_strdup(data);
	if (s_node.var == NULL || s_node.data == NULL)
		return (FAILURE);
	if ((newdir = ft_lstnew(&s_node, sizeof(t_node))) == NULL)
		return (FAILURE);
	ft_lstaddback(alst, newdir);
	return (SUCCESS);
}

int8_t			change_node(t_list **alst, char *var, char *data)
{
	t_list *ptr;

	ptr = *alst;
	if (name == NULL || data == NULL)
		return (FAILURE);
	while (ptr != NULL)
	{
		if (ft_strequ(((t_variable *)ptr->data)->name, name) == TRUE)
		{
			free(((t_variable *)ptr->data)->data);
			((t_variable *)ptr->data)->data = data;
			return (SUCCESS);
		}
		ptr = ptr->next;
	}
	return (s_create_node(alst, name, data));
}

int8_t			search_data(t_list **alst, char *var)
{
	t_list *ptr;

	ptr = *alst;
	while (ptr != NULL)
	{
		if (ft_strequ(((t_variable *)ptr->data)->name, name) == TRUE)
			return (SUCCESS);
		ptr = ptr->next;
	}
	return (FAILURE);
}

char			*get_data(t_list **alst, char *name)
{
	t_list *ptr;

	ptr = *alst;
	while (ptr != NULL)
	{
		if (ft_strequ(((t_variable *)ptr->data)->name, name) == TRUE)
			return (((t_variable *)ptr->data)->data);
		ptr = ptr->next;
	}
	return (NULL);
}
