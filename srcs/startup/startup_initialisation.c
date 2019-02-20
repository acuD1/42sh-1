/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   startup_initialisation.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 14:33:03 by skuppers          #+#    #+#             */
/*   Updated: 2019/02/19 16:25:15 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "startup.h"
#include "libft.h"

/*
 *	Look out for /etc/profile if it is a login shell invocation
 *		-> ~/.42sh_profile
 *		-> ~/.42sh_login
 *		-> ~/.profile
 *	else
 *		-> ~/.42sh/.42rc
 */

t_data_list prepare_data_structures()
{
	/*
	 *	malloc essential data structures
	 *	and memset(0) them
	 */
}
