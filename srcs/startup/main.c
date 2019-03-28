/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 13:19:49 by nrechati          #+#    #+#             */
/*   Updated: 2019/03/28 17:31:52 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "21sh.h"
#include "log.h"
#include <stdlib.h>

int		main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	(void)env;
	t_registry *registry;

	registry = malloc(sizeof(t_registry));

	init_debug_logger(registry);
	shell_invoke_interactive(registry);
	return (0);
}
