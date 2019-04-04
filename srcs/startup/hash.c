/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 15:27:08 by nrechati          #+#    #+#             */
/*   Updated: 2019/04/04 10:59:24 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#include <unistd.h>

int		hash_bltin(t_registry *reg)
{
	int				i;
	DIR				*dip;
	struct dirent	*dit;
	char			**tab;
	char			*asp;

	if (reg->bin_hashmap.used > 0)
		ft_hmap_free_content(&(reg->bin_hashmap), free);
	tab = ft_strsplit(get_data(&(reg->env), "PATH"), ":");
	if (!tab)
		return (0);
	i = 0;
	while (tab[i])
	{
		if ((dip = opendir(tab[i])) != NULL)
		{
			while ((dit = readdir(dip)) != NULL)
			{
				asp = NULL;
				ft_asprintf(&asp, "%s/%s", tab[i],dit->d_name);
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
		}
		closedir(dip);
		i++;
	}
	ft_freetab(&tab);
	return (1);
}
