/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_blt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 18:11:50 by ffoissey          #+#    #+#             */
/*   Updated: 2019/04/24 18:57:05 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

t_option			get_option_env(char *s, t_option option)
{
	while (*s)
	{
		if (*s == 'i')
			option |= I_OPT;
		else
		{
			ft_dprintf(2, "21sh: env: -%c: invalid option\n", *s);
			ft_dprintf(2, ENV_USAGE);
			return (ERROR_OPT);
		}
		s++;
	}
	return (option);
}


static void				ft_fill_with_new_value(t_registry *cpy_shell,
						char ***arg)
{
	char		*equal;
	t_node		*node;

	while ((equal = ft_strchr(**arg, '=')))
	{
		node = (t_node *)malloc(sizeof(t_node));
		node->var = ft_strdup(**arg);
		equal = ft_strchr(node->var, '=');
		*equal = '\0';
		node->data = ft_strdup(ft_strchr(**arg, '=') + 1);
		add_env(cpy_shell, node->var, node->data);
		(*arg)++;
	}
}

static t_registry		*copy_registry(t_registry *shell, char ***arg,
						t_option option)
{
	t_node		*node;
	t_list		*lst;
	t_registry	*cpy_shell;

	cpy_shell = (t_registry *)ft_memalloc(sizeof(*shell));
	cpy_shell = ft_memcpy(cpy_shell, shell, sizeof(*shell));
	cpy_shell->env = NULL;
	if (!option)
	{
		lst = shell->env;
		while (lst)
		{
			node = (t_node *)malloc(sizeof(t_node));
			node->var = ft_strdup(((t_node *)(lst->data))->var);
			node->data = ft_strdup(((t_node *)(lst->data))->data);
			add_env(cpy_shell, node->var, node->data);
			lst = lst->next;
		}
	}
	ft_fill_with_new_value(cpy_shell, arg);
	return (cpy_shell);
}


int8_t				env_blt(t_registry *shell, char **av)
{
	t_option	option;
	t_registry	*cpy_shell;

	av++;
	option = 0;
	if (av && ft_strequ(*av, "-"))
	{
		av++;
		option = I_OPT;
	}
	else if (((option |= set_options(&av, get_option_env)) == ERROR_OPT))
		return (FAILURE);
	cpy_shell = copy_registry(shell, &av, option);
	if (!*av)
		print_env(cpy_shell->env);
	free_lst(&(cpy_shell->env));
/////////////////////////////// SEND TO EXECUTION //////////////////// 	
/////////////////////////////// exec(cpy_shell, av); //////////////////
	free(cpy_shell);
	cpy_shell = NULL;
	return (SUCCESS);
}
