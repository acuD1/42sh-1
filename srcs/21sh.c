/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   21sh.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 10:41:54 by skuppers          #+#    #+#             */
/*   Updated: 2019/01/07 11:50:26 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#include "log.h"
#include "line_edit.h"
#include "libft.h"

int		main(int ac, char **av, char **environ)
{
	if (ac && av && environ)
		log_print(LOG_OK, "Init variables are present.\n");

	//Place to do stuff before line edition init

	//Initialise termcaps directives
	init_line_edition(environ);

	//Place to do stuff after line edition init

	//Main prompt
	prompt();

	return (0);
}
