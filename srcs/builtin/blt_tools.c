/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 18:11:41 by ffoissey          #+#    #+#             */
/*   Updated: 2019/04/24 18:11:43 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static enum e_state_option	is_option(char *s)
{
	if (ft_strequ(s, "--"))
		return (E_END_OPTION);
	else if (*s == '-' && *(s + 1) != '\0')
		return (E_OPTION);
	return (E_NO_OPTION);
}

t_option					set_options(char ***av, t_get_option get_option)
{
	enum e_state_option	state;
	t_option			option;
	t_option			new_option;

	state = E_START_OPTION;
	option = 0;
	if (!av)
		return (option);
	while (**av)
	{
		state = is_option(**av);
		if (state == E_NO_OPTION)
			return (option);
		else if (state == E_OPTION)
		{
			if ((new_option = get_option(**av + 1)) == ERROR_OPT)
				return (ERROR_OPT);
			option |= get_option(**av + 1);
		}
		(*av)++;
	}
	return (option);
}
