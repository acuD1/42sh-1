/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_blt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 11:26:20 by ffoissey          #+#    #+#             */
/*   Updated: 2019/04/27 12:15:12 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "21sh.h"

static void	free_opt(t_opt option)
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

static void	free_hash(t_hash hashmap, void (*del)(void *))
{
	ft_hmap_free_content(&hashmap, del);
	free(hashmap.map);
}

static void	free_registry(t_registry *reg)
{
	free_opt(reg->option);
	free_lst(&(reg->env));
	free_lst(&(reg->intern));
	free_hash(reg->bin_hashmap, free);
	free_hash(reg->blt_hashmap, NULL);
}

static int			ft_is_numeric(char *s)
{
	while (*s)
	{
		if (!ft_isdigit(*s))
			return (0);
	}
	return (1);
}

int8_t				exit_blt(t_registry *shell, char **av)
{
	av++;
	if (*av)
	{
		if (!ft_is_numeric(*av))
		{
			ft_dprintf(2, "21sh: exit: %s: numeric argument required", *av);
			free_registry(shell);
			exit(-1);
		}
		else if (*(av + 1))
		{
			ft_dprintf(2, "21sh: exit: too many argument");
			return (1);
		}
		else
		{
			free_registry(shell);
			exit(ft_atoi(*av));
		}
	}
	free_registry(shell);
	exit(0);
}
