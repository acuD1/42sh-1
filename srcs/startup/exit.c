/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 09:37:06 by nrechati          #+#    #+#             */
/*   Updated: 2019/04/04 15:58:49 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

void	free_opt(t_opt option)
{
	if (option.cmd)
	{
		free(option.cmd);
		option.cmd = NULL;
	}
	if (option.path)
	{
		free(option.path);
		option.path = NULL;
	}
}

void	free_hash(t_hash hashmap, void (*del)(void *))
{
	ft_hmap_free_content(&hashmap, del);
	free(hashmap.map);
}

void	free_registry(t_registry *reg)
{
	free_opt(reg->option);
	free_lst(&(reg->env));
	free_lst(&(reg->intern));
	free_hash(reg->bin_hashmap, free);
	free_hash(reg->blt_hashmap, NULL);
}

int		exit_blt(t_registry *reg)
{
	free_registry(reg);
	return (1);
}
