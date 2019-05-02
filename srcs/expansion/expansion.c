/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 00:58:53 by cempassi          #+#    #+#             */
/*   Updated: 2019/05/02 18:49:25 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#include "parser.h"

char	character_swap(char swapped)
{
	static char previous = '\0';
	char		c;

	c = previous;
	previous = swapped;
	return (c);
}

char	*string_expansion(t_parser *parse, char *str)
{
	str = tilde(parse, str);
	str = variable_expansion(parse, str);
	return (str);
}
