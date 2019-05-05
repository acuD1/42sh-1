/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_blt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 11:26:20 by ffoissey          #+#    #+#             */
/*   Updated: 2019/05/04 19:42:32 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#include "libft.h"

static void		free_opt(t_opt option)
{
	ft_strdel(&option.command_str);
//	free(option.path);
//	option.path = NULL;
}

static void		free_hash(t_hash hashmap, void (*del)(void *))
{
	ft_hmap_free_content(&hashmap, del);
	free(hashmap.map);
	hashmap.map = NULL;
}

void			free_registry(t_registry *reg)
{
	free_opt(reg->option);
	free_lst(&(reg->env));
	free_lst(&(reg->intern));
	free_hash(reg->bin_hashmap, free);
	free_hash(reg->blt_hashmap, NULL);
}

int8_t			exit_blt(t_registry *shell, char **av)
{
	++av;
	if (*av != NULL)
	{
		if (ft_isnumeric(*av) == FALSE)
		{
			ft_dprintf(shell->cur_fd.err,
					"21sh: exit: %s: numeric argument required\n", *av);
			free_registry(shell);
			exit(FAILURE);
		}
		else if (*(av + 1) != NULL)
		{
			ft_dprintf(shell->cur_fd.err, "21sh: exit: too many argument\n");
			return (1);
		}
	}
	free_registry(shell);
	exit(*av == NULL ? SUCCESS : ft_atoi(*av));
}
