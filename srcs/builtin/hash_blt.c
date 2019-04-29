/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_blt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 12:09:44 by ffoissey          #+#    #+#             */
/*   Updated: 2019/04/29 16:25:05 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "builtin.h"

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
			if (asp != NULL)
			{
				if (dit->d_name[0] != '.')
				{
					if (ft_hmap_insert(&(reg->bin_hashmap)
							, dit->d_name, asp) == FALSE)
						free(asp);
				}
				else
					free(asp);
			}
		}
		if (closedir(dip) == SUCCESS)
			return ;
	}
}

static void	hash_builtin(t_registry *reg)
{
	ft_hmap_insert(&(reg->blt_hashmap), "echo", echo_blt);
	ft_hmap_insert(&(reg->blt_hashmap), "cd", cd_blt);
	ft_hmap_insert(&(reg->blt_hashmap), "setenv", setenv_blt);
	ft_hmap_insert(&(reg->blt_hashmap), "unsetenv", unsetenv_blt);
	ft_hmap_insert(&(reg->blt_hashmap), "env", env_blt);
	ft_hmap_insert(&(reg->blt_hashmap), "hash", hash_blt);
	ft_hmap_insert(&(reg->blt_hashmap), "exit", exit_blt);
	ft_hmap_insert(&(reg->blt_hashmap), "intern", intern_blt);
}

int8_t			hash_blt(t_registry *reg, char **av)
{
	int				i;
	char			**tabs;

	(void)av;
	if (reg->bin_hashmap.used > 0)
		ft_hmap_free_content(&(reg->bin_hashmap), free);
	if (get_data(&(reg->env), "PATH") != NULL)
	{
		tabs = ft_strsplit(get_data(&(reg->env), "PATH"), ":");
		if (tabs == NULL)
			return (FAILURE);
		i = 0;
		while (tabs[i] != NULL)
			hash_bin(reg, tabs[i++]);
		ft_freetab(&tabs);
	}
	hash_builtin(reg);
	if (reg->blt_hashmap.used == FALSE)
		ft_dprintf(2, "Hashmap blt is empty.\n");
	return (SUCCESS);
}

/*
** builtin = (t_builtin)ft_hmap_getdata(&(reg->blt_hashmap), "hash");
** if (builtin)
** 	if (!builtin(reg))
** 		return (0);
*/
