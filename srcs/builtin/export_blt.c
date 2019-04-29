/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_blt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 18:11:50 by ffoissey          #+#    #+#             */
/*   Updated: 2019/04/27 14:35:28 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

t_option			get_option_export(char *s, t_option option)
{
	while (*s)
	{
		if (*s == 'p')
			option |= P_OPT;
		else
		{
			ft_dprintf(2, "21sh: export: -%c: invalid option\n", *s);
			ft_dprintf(2, EXPORT_USAGE_1);
			ft_dprintf(2, ENV_USAGE_2);
			return (ERROR_OPT);
		}
		s++;
	}
	return (option);
}

int8_t				export_blt(t_registry *shell, char **av)
{
	t_node		*node;
	char		*equal;
	t_option	option;

	av++;
	option = 0;
	//////////////// implement option -p
	if (((option |= set_options(&av, get_option_export)) == ERROR_OPT))
		return (FAILURE);
	while (*av) 
	{
		node = (t_node *)malloc(sizeof(t_node));
		node->var = ft_strdup(*av);
		if ((equal = ft_strchr(*av, '=')) != NULL)
		{
			equal = ft_strchr(node->var, '=');
			*equal = '\0';
			node->data = ft_strdup(ft_strchr(*av, '=') + 1);
		}
		else
			node->data = ft_strdup(get_intern_var(shell, node->var));
		add_env(shell, node->var, node->data);
	//	if (node && node->var && ft_strequ(node->var, "PATH"))
	//		hash_blt(shell, av);
		clear_node((void **)&node);
		free(node);
		av++;
	}
	return (SUCCESS);
}
