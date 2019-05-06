/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_blt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 18:11:50 by ffoissey          #+#    #+#             */
/*   Updated: 2019/04/30 21:12:53 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "21sh.h"

t_registry *g_shell;

t_option			get_option_export(char *s, t_option option)
{
	while (*s)
	{
		if (*s == 'p')
			option |= P_OPT;
		else
		{
			ft_dprintf(g_shell->cur_fd.err,
						"21sh: export: -%c: invalid option\n", *s);
			ft_dprintf(g_shell->cur_fd.err, EXPORT_USAGE);
			return (ERROR_OPT);
		}
		s++;
	}
	return (option);
}

int8_t				export_blt(t_registry *shell, char **av)
{
	t_variable	*variable;
	char		*equal;
	t_option	option;

	av++;
	option = 0;
	//////////////// implement option -p
	if (((option |= set_options(&av, get_option_export)) == ERROR_OPT))
		return (FAILURE);
	while (*av != NULL)
	{
		if ((variable = (t_variable *)malloc(sizeof(t_variable))) == NULL)
			return (FAILURE);
		variable->name = ft_strdup(*av);
		if ((equal = ft_strchr(*av, '=')) != NULL)
		{
			equal = ft_strchr(variable->name, '=');
			*equal = '\0';
			variable->data = ft_strdup(ft_strchr(*av, '=') + 1);
		}
		else
			variable->data = ft_strdup(get_intern_var(shell, variable->name));
		if (variable->data)
			add_env(shell, variable->name, variable->data);
		if (variable && variable->name && ft_strequ(variable->name, "PATH"))
			hash_blt(shell, av);
		clear_node((void **)&variable);
		free(variable);
		av++;
	}
	return (SUCCESS);
}
