/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 11:03:23 by nrechati          #+#    #+#             */
/*   Updated: 2019/04/18 15:21:55 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "resolve.h"

static int		test3_echo(t_instr *cmd, char **env)
{
	char		**split;

	split = malloc(sizeof(char*) * 3);
	split[0] = ft_strdup("echo");
	split[1] = ft_strdup("Echo was here");
	split[2] = NULL;
	cmd->ac = 2;
	cmd->av = split;
	cmd->env = env;
	cmd->fd_in = 0;
	cmd->fd_out = open("./echofile", O_RDWR | O_TRUNC | O_CREAT, 0666);
	cmd->fd_err = 2;
	cmd->gid = 0;
	if (!cmd->av)
		return (0);
	return (1);
}

t_list			*test3(void)
{
	t_list	*test;

	test = NULL;
	add_to_test(&test, test3_echo);
	return (test);
}
