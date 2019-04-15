/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 13:19:49 by nrechati          #+#    #+#             */
/*   Updated: 2019/04/15 15:13:58 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "21sh.h"
#include "log.h"
#include "line_edit.h"
#include "interface_functions.h"

void	print_opt(t_registry *reg)
{
	log_print(reg, LOG_INFO, "Options: \n");
	log_print(reg, LOG_INFO, "| h=%d | v=%d | d=%d | norc=%d |\n",
			reg->option.h, reg->option.v, reg->option.d, reg->option.norc);
	log_print(reg, LOG_INFO, "| c=%d | cmd=%s | rcfile=%d | path=%s |\n",
			reg->option.c, reg->option.cmd
			, reg->option.rcfile, reg->option.path);
}

int		main(int ac, char **av, char **env)
{
	t_builtin	blt;
	t_registry	registry;

	ft_bzero(&registry, sizeof(t_registry));
	if (!launch_sh(ac, av, env, &registry))
		return (0);

	init_debug_logger(&registry);
	print_opt(&registry);
	shell_invoke_interactive(&registry);

	blt = (t_builtin)ft_hmap_getdata(&(registry.blt_hashmap), "exit");
	if (blt)
		if (!blt(&registry))
			return (0);
	return (0);
}
