/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 13:19:49 by nrechati          #+#    #+#             */
/*   Updated: 2019/04/27 13:02:16 by ffoissey         ###   ########.fr       */
/*   Updated: 2019/04/26 14:23:34 by skuppers         ###   ########.fr       */
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
	t_registry	registry;

	ft_bzero(&registry, sizeof(t_registry));
	if (launch_sh(ac, av, env, &registry))
		return (FAILURE);
	init_debug_logger(&registry);

	//TODO: Set up parser graphs
	// & program wide used variables

	print_opt(&registry); // print options, handle them

	//TODO: Handle interactive or not
	//	isatty() or not
	//	ex: echo "ls" | 21sh
	//	etc...

	shell_invoke_interactive(&registry);
	return (SUCCESS);
}
