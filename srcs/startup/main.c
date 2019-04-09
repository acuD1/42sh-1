/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 13:19:49 by nrechati          #+#    #+#             */
/*   Updated: 2019/04/07 13:38:30 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "21sh.h"
#include "log.h"
#include "line_edit.h"


void 	print_opt(t_registry *reg)
{
	log_print(reg, LOG_INFO, "Options: \n");
	log_print(reg, LOG_INFO, "| h=%d | v=%d | d=%d | norc=%d |\n",
			reg->option.h, reg->option.v, reg->option.d, reg->option.norc);
	log_print(reg, LOG_INFO, "| c=%d | cmd=%s | rcfile=%d | path=%s |\n",
			reg->option.c, reg->option.cmd, reg->option.rcfile, reg->option.path);
}

int		main(int ac, char **av, char **env)
{
	t_registry	registry;

	if (!launch_sh(ac, av, env, &registry))
		return (0);

	while (*env)
		ft_printf("%s\n", *env++);

	init_debug_logger(&registry);

	print_opt(&registry);

	shell_invoke_interactive(&registry);

	ft_strdel(&(registry.option.cmd));
	ft_strdel(&(registry.option.path));
	free_lst(&(registry.env));
	free_lst(&(registry.intern));
	return (0);
}
