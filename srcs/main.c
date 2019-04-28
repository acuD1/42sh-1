/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 13:19:49 by nrechati          #+#    #+#             */
/*   Updated: 2019/04/27 16:35:05 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "21sh.h"
#include "log.h"
#include "interface_functions.h"
#include "parser.h"
#include "resolve.h"

void	print_opt(t_registry *reg)
{
	log_print(reg, LOG_INFO, "Options: \n");
	log_print(reg, LOG_INFO, "| h=%d | v=%d | d=%d | norc=%d |\n",
			reg->option.h, reg->option.v, reg->option.d, reg->option.norc);
	log_print(reg, LOG_INFO, "| c=%d | cmd=%s | rcfile=%d | path=%s |\n",
			reg->option.c, reg->option.cmd
			, reg->option.rcfile, reg->option.path);
}

char	*read_input(int fd)
{
	char	*final;
	char	*str;
	char	buffer[16];

	str = NULL;
	final = NULL;
	ft_memset(buffer, 0, sizeof(char) * 16);
	while (read(fd, buffer, 16) > 0)
	{
		str = final;
		ft_strdel(&final);
		ft_asprintf(&final, "%s%s", str, buffer);
	}
	return (final);
}

static int		init_shell(t_registry *shell, char **av, char **env)
{
	ft_bzero(shell, sizeof(t_registry));
	if (launch_sh(av, env, shell) == FAILURE)
		return (FAILURE);
	init_parser(&shell->parser);
	shell->parser.env = shell->env;
	init_debug_logger(shell);
	generate_graph(shell);
	if (shell->option.c == FALSE && isatty(STDIN_FILENO) != 0)
	{
		if ((load_interface(shell)) == FAILURE)
		{
			ft_printf("[CRITICAL] - Interface setup failed.\n");
			log_print(shell, LOG_INFO, "Restoring original shell behavior.\n");
			restore_term_behavior(shell);
			log_print(shell, LOG_INFO, "Releasing interface memory.\n");
			free_interface_registry(&shell->interface);
			return (FAILURE);
		}
	}
	return (SUCCESS);
}

int		main(int ac, char **av, char **env)
{
	t_registry		shell;
	char 			*command;

	(void)ac;
	
	if (init_shell(&shell, av, env) == FAILURE)
		return (FAILURE);
	g_shell_registry = &shell;
	print_opt(&shell); // print options, handle them
	if (shell.option.c == FALSE && isatty(STDIN_FILENO) != 0)
	{
		shell_invoke_interactive(&shell);
	}
	else
	{

		command = (shell.option.c == TRUE)
			? shell.option.cmd : read_input(STDIN_FILENO);

		ft_dprintf(1, "CMD:%s\n", command);
		/*int ret_lex_parse = lexer_parser(shell.parser, shell.option.cmd);
		if (ret_lex_parse == SUCCESS)
		{
			launch_job(&shell, shell.parser->job_list);
			ft_lstdel(&shell.parser->job_list, delete_job);
		}*/
	}

	// exit routines
	// & cleanup
	// Clean all environment variables
	// Clean all intern variables

	return (SUCCESS);
}
