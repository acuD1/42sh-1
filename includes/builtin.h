/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 16:35:32 by ffoissey          #+#    #+#             */
/*   Updated: 2019/04/24 17:49:54 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef BUILTIN_H
# define BUILTIN_H

# include "interface_functions.h"

# define SUCCESS	0
# define FAILURE	-1

# define N_OPT		0x0000000000000001
# define ERROR_OPT	0x1000000000000000

# define ERROR_ECHO 

typedef unsigned long t_option;
typedef t_option (*t_get_option)(char *s);

enum e_state_option
{
	E_START_OPTION,
	E_OPTION,
	E_END_OPTION,
	E_NO_OPTION

};

int8_t				echo_blt(t_registry *shell, char **av);
t_option			get_option_echo(char *s, char *builtin_name);



#endif
