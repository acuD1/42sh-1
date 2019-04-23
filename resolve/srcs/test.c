/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 10:30:27 by nrechati          #+#    #+#             */
/*   Updated: 2019/04/23 16:40:22 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "resolve.h"
#include "reso.h"

int 	fill_test_bank(t_hash *hashmap)
{
	if (!ft_hmap_insert(hashmap, "test1", test1()))
		return (ft_dprintf(2, "\x1b[31m[ERROR]: Failed to insert TEST 1 to hashmap\n\x1b[0m") & 0);
	return (1);
}

char	*get_line(char	*test)
{
	if (!ft_strcmp(test, "test1"))
		return (EXEC_TEST_1);
	if (!ft_strcmp(test, "test2"))
		return (EXEC_TEST_2);
	if (!ft_strcmp(test, "test3"))
		return (EXEC_TEST_3);
	if (!ft_strcmp(test, "test4"))
		return (EXEC_TEST_4);
	if (!ft_strcmp(test, "test5"))
		return (EXEC_TEST_5);
	if (!ft_strcmp(test, "test6"))
		return (EXEC_TEST_6);
	if (!ft_strcmp(test, "test7"))
		return (EXEC_TEST_7);
	if (!ft_strcmp(test, "test8"))
		return (EXEC_TEST_8);
	if (!ft_strcmp(test, "testA"))
		return (EXEC_TEST_A);
	if (!ft_strcmp(test, "testB"))
		return (EXEC_TEST_B);
	if (!ft_strcmp(test, "testC"))
		return (EXEC_TEST_C);
	if (!ft_strcmp(test, "testD"))
		return (EXEC_TEST_D);
	if (!ft_strcmp(test, "testE"))
		return (EXEC_TEST_E);
	return	(NULL);
}
