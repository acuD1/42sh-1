/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 13:27:44 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/27 16:22:33 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UNIT_21_SH
# define UNIT_21_SH

#include "21sh.h"
#include "log.h"
#include "interface_functions.h"
#include <stdlib.h>

t_result	test_virt_registry(int print_on);
t_result	test_clipboard_copy(int print_on);
t_result	test_clipboard_cut(int print_on);
t_result	test_clipboard_paste(int print_on);

int			create_virtual_registry(t_registry **sh, t_interface **itf);

t_result	basic_lexer_test(int print_on);

#endif
