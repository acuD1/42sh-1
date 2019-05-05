/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_blt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 18:11:50 by ffoissey          #+#    #+#             */
/*   Updated: 2019/04/27 14:35:28 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
/*
t_option		get_option_type(char *s, t_option option)
{
	option = 0;
	while (*s)
	{
		if (*s == 'a')
			option |= A_OPT;
		else if (*s == 'f')
			option |= F_OPT;
		else if (*s == 'p')
			option |= P_LOW_OPT;
		else if (*s == 't')
			option |= T_OPT;
		else if (*s == 'P')
			option |= P_OPT;
		else
		{
			ft_dprintf(2, "21sh: type: -%c: invalid option\n", *s);
			ft_dprintf(2, TYPE_USAGE);
			return (ERROR_OPT);
		}
		s++;
	}
	return (option);
}
*/
int8_t				type_blt(t_registry *shell, char **av)
{
	char		*path_bin;
	int8_t		error;
	//t_option	option;

	///////// IMPLEMENT OPT
	av++;
	error = SUCCESS;
	///////// implement for absolute path binary : ex: /bin/ls
/*	if (*av == NULL
		|| (option = set_options(&av, get_option_type)) == ERROR_OPT)
		return (FAILURE);*/
	while (*av != NULL)
	{
		if (ft_hmap_getdata(&shell->blt_hashmap, *av) != NULL)
			ft_dprintf(shell->cur_fd.out, "%s is a shell builtin\n", *av);
		else if ((path_bin = ft_hmap_getdata(&shell->bin_hashmap, *av))
					!= NULL)
			ft_dprintf(shell->cur_fd.out, "%s is %s\n", *av, path_bin);
		else
		{
			error = 1;
			ft_dprintf(shell->cur_fd.err, "21sh: type: %s: not found\n", *av);
		}
		av++;
	}
	return (error);
}
