/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 15:27:08 by nrechati          #+#    #+#             */
/*   Updated: 2019/04/04 14:04:37 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#include <unistd.h>

static void	hash_bin(t_registry *reg, char *bin)
{
	char			*asp;
	DIR				*dip;
	struct dirent	*dit;

	if ((dip = opendir(bin)) != NULL)
	{
		while ((dit = readdir(dip)) != NULL)
		{
			asp = NULL;
			ft_asprintf(&asp, "%s/%s", bin, dit->d_name);
			if (asp)
			{
				if (dit->d_name[0] != '.')
				{
					if (!ft_hmap_insert(&(reg->bin_hashmap), dit->d_name, asp))
						free(asp);
				}
				else
					free(asp);
			}
		}
		if (!closedir(dip))
			return ;
	}
}

static void	hash_builtin(t_registry *reg)
{
	if (!ft_hmap_insert(&(reg->blt_hashmap), "echo", exit_blt))
		ft_dprintf(2, "[ERROR] Hmap insert failure : echo built-in\n");
	if (!ft_hmap_insert(&(reg->blt_hashmap), "cd", exit_blt))
		ft_dprintf(2, "[ERROR] Hmap insert failure : cd built-in\n");
	if (!ft_hmap_insert(&(reg->blt_hashmap), "setenv", exit_blt))
		ft_dprintf(2, "[ERROR] Hmap insert failure : setenv built-in\n");
	if (!ft_hmap_insert(&(reg->blt_hashmap), "unsetenv", exit_blt))
		ft_dprintf(2, "[ERROR] Hmap insert failure : unsetenv built-in\n");
	if (!ft_hmap_insert(&(reg->blt_hashmap), "env", exit_blt))
		ft_dprintf(2, "[ERROR] Hmap insert failure : env built-in\n");
	if (!ft_hmap_insert(&(reg->blt_hashmap), "hash", hash_blt))
		ft_dprintf(2, "[ERROR] Hmap insert failure : hash built-in\n");
	if (!ft_hmap_insert(&(reg->blt_hashmap), "exit", exit_blt))
		ft_dprintf(2, "[ERROR] Hmap insert failure : exit built-in\n");
}

int			hash_blt(t_registry *reg)
{
	int				i;
	char			**tab;

	if (reg->bin_hashmap.used > 0)
		ft_hmap_free_content(&(reg->bin_hashmap), free);
	tab = ft_strsplit(get_data(&(reg->env), "PATH"), ":");
	if (!tab)
		return (0);
	i = 0;
	while (tab[i])
		hash_bin(reg, tab[i++]);
	hash_builtin(reg);
	ft_freetab(&tab);
	return (1);
}

/*
** builtin = (t_builtin)ft_hmap_getdata(&(reg->blt_hashmap), "hash");
** if (builtin)
** 	if (!builtin(reg))
** 		return (0);
*/
