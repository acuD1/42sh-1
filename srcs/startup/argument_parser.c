/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 14:32:15 by skuppers          #+#    #+#             */
/*   Updated: 2019/02/25 10:44:32 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "startup.h"
#include "21sh.h"

void	set_arguments(int i, char **av, t_arguments *args)
{
	unsigned int y;

	y = 1;
	while (av[i][y] != '\0')
	{
		if (av[i][y] == 'c')
		{
			args->opt_i = 0;
			args->opt_c = 1;
			if (av[i + 1] != NULL)
				args->c_param = ft_strdup(av[i + 1]);
		}
		else if (av[i][y] == 'i')
		{
			args->opt_c = 0;
			ft_strdel(&(args->c_param));
			args->c_param = NULL;
			args->opt_i = 1;
		}
		else if (av[i][y] == 'l')
		{
			args->opt_l = 1;
		}
		else if (av[i][y] == 'd')
		{
			args->opt_d = 1;
		}
		else if (av[i][y] == 'v')
		{
			args->opt_v = 1;
		}
		else if (av[i][y] == 'n')
		{
			args->opt_n = 1;
		}
		else if (av[i][y] == 'h')
		{
			args->opt_h = 1;
		}
		++y;
	}
}
t_arguments		*parse_arguments(int ac, char **av)
{
	/*
	 * Parsing args
	 *  -- stops args parsing
	 *  -c "string"
	 *	-i      -> interactive (default)
	 *	-l || --login     -> login shell
	 *	-d || --debug     -> live debug to tty
	 *	--version 	      -> print version
	 *	--noprofile       -> noprofile login shell invokation
	 *	--help            -> displays shell user info
	 *	--posix           -> posix invokation
	 *	--norc			  -> dont read .rc file
	 *	--rcfile "file"   -> use file instead of standart rc file
	 */

	t_arguments		*args;
	unsigned int	i;

	if (!(args = malloc(sizeof(t_arguments))))
		return (NULL);
	ft_memset(args, 0, sizeof(t_arguments));
	args->opt_i = 1;
	if (ac == 1)
		return (args);
	else
	{
		i = 1;
		while (i < (unsigned int)ac)
		{
			if (av[i][0] == '-')
				set_arguments(i, av, args);
			++i;
		}
	}
	return (args);
}
