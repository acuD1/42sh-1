/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 13:27:44 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/09 15:53:29 by skuppers         ###   ########.fr       */
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

int test_insertion(void);
int test_deletion(void);
int	test_clipboard(void);
int	test_null_value(void);
int	test_arrow_keys(void);
int test_virt_registry(void);
int	create_virtual_registry(t_registry **sh, t_interface_registry **itf);

#endif
