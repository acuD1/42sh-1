/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 14:32:15 by skuppers          #+#    #+#             */
/*   Updated: 2019/03/20 13:45:05 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "startup.h"
#include "21sh.h"

/*
t_arguments		*parse_arguments(int ac, char **av)
{
	 * Parsing args
	 *  -- stops args parsing
	 *  -c "string"
	 *	-i      -> interactive (default)
	 *	-l || --login     -> login shell
	 *	-d || --debug     -> live debug to tty
	 *	--version 	      -> print version
	 *	--noprofile       -> noprofile login shell invokation
	 *	--help            -> displays shell user info
	 *
	 *	--norc			  -> dont read .rc file
	 *	--rcfile "file"   -> use file instead of standart rc file


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
*/
