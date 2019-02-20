/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 14:32:15 by skuppers          #+#    #+#             */
/*   Updated: 2019/02/20 14:01:12 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "startup.h"

unsigned int	parse_arguments(int ac, char **av)
{
	/*
	 * Parsing args
	 *  -c "string"
	 *	-i -> interactive (default)
	 *	-l | --login      -> login shell
	 *	-d | --debug-live -> live debug to tty
	 *	-v | --version    -> print version
	 *	-n | --noprofile  -> noprofile login shell invokation
	 *
	 * return u-int.
	 * /
}
