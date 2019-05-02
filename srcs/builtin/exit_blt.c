/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_blt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 11:26:20 by ffoissey          #+#    #+#             */
/*   Updated: 2019/04/30 16:54:31 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "21sh.h"

static void	free_opt(t_opt option)
{
	if (option.command_str)
	{
		free(option.command_str);
		option.command_str = NULL;
	}
//	if (option.path)
//	{
//		free(option.path);
//		option.path = NULL;
//	}
}

static void	free_hash(t_hash hashmap, void (*del)(void *))
{
	ft_hmap_free_content(&hashmap, del);
	free(hashmap.map);
	hashmap.map = NULL;
}

void	free_registry(t_registry *reg)
{
	free_opt(reg->option);
	free_lst(&(reg->env));
	free_lst(&(reg->intern));
	free_hash(reg->bin_hashmap, free);
	free_hash(reg->blt_hashmap, NULL);
}

static int			ft_is_numeric(char *s)
{
	if (*s == '-')
		s++;
	if (*s == '\0')
		return (FALSE);
	while (*s != '\0')
	{
		if (ft_isdigit(*s) == FALSE)
			return (FALSE);
		s++;
	}
	return (TRUE);
}

int8_t				exit_blt(t_registry *shell, char **av)
{
	av++;
	if (av != NULL && *av != NULL)
	{
		if (ft_is_numeric(*av) == FALSE)
		{
			ft_dprintf(2, "21sh: exit: %s: numeric argument required\n", *av);
			free_registry(shell);
			exit(FAILURE);
		}
		else if (*(av + 1) != NULL)
		{
			ft_dprintf(2, "21sh: exit: too many argument\n");
			return (1);
		}
	}
	free_registry(shell);
	exit(*av == NULL ? SUCCESS : ft_atoi(*av));
}
