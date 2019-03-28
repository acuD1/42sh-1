/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 13:19:49 by nrechati          #+#    #+#             */
/*   Updated: 2019/03/26 16:31:31 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "21sh.h"

int		main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	(void)env;
	shell_invoke_interactive(NULL);
	return (0);
}
