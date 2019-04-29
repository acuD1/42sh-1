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

int8_t				type_blt(t_registry *shell, char **av)
{
	char	*path_bin;
	int8_t	error;

	av++;
	error = SUCCESS;
	if (av[0] == NULL)
		return (FAILURE);
	while (*av != NULL)
	{
		if (ft_hmap_getdata(&shell->blt_hashmap, av[0]) != NULL)
			ft_printf("%s is a shell builtin\n", av[0]);
		else if ((path_bin = ft_hmap_getdata(&shell->bin_hashmap, av[0]))
					!= NULL)
			ft_printf("%s is %s\n", av[0], path_bin);
		else
		{
			error = 1;
			ft_dprintf(2, "21sh: type: %s: not found\n", av[0]);
		}
		av++;
	}
	return (error);
}
