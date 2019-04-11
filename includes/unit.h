/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 13:27:44 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/11 17:13:24 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UNIT_21_SH
# define UNIT_21_SH

#include "libft.h"
#include "21sh.h"
#include "log.h"
#include "line_edit.h"
#include "internals.h"
#include <stdlib.h>
#define BLUE "39"
#define TRUE 0
#define FALSE -1
#define T_CHMOD 766
#define HOME "/Users/skuppers"

t_result	test_wjump(int print_on);
t_result	test_insertion(int print_on);
t_result	test_deletion(int print_on);
t_result	test_clipboard(int print_on);
t_result	test_null_value(int print_on);
t_result	test_arrow_keys(int print_on);
t_result	test_virt_registry(int print_on);
int			create_virtual_registry(t_registry **sh, t_interface_registry **itf);

#endif
