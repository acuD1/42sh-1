/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 13:19:49 by nrechati          #+#    #+#             */
/*   Updated: 2019/04/20 06:44:07 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#include "log.h"

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
	//t_builtin	blt;
	t_registry	shell;

	if (!isatty(STDIN_FILENO) || !isatty(STDOUT_FILENO))
	{
		ft_dprintf(2,"STDIN or STDOUT is not a valid tty.\n");
		return (0);
	}
	if (ac == 0)
		;
	ft_bzero(&shell, sizeof(t_registry));
	if (!launch_sh(av, env, &shell))
		return (0);
	init_debug_logger(&shell);
	print_opt(&shell);
	shell_invoke_interactive(&shell);
	//blt = (t_builtin)ft_hmap_getdata(&(shell.blt_hashmap), "exit");
	//if (blt)
	//	if (!blt(&shell))
	///		return (0);
	return (0);
}
