/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 10:30:27 by nrechati          #+#    #+#             */
/*   Updated: 2019/04/18 17:16:07 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "resolve.h"

int 	fill_test_bank(t_hash *hashmap)
{
	if (!ft_hmap_insert(hashmap, "test1", test1()))
		return (ft_dprintf(2, "\x1b[31m[ERROR]: Failed to insert TEST 1 to hashmap\n\x1b[0m") & 0);
	if (!ft_hmap_insert(hashmap, "test2", test2()))
		return (ft_dprintf(2, "\x1b[31m[ERROR]: Failed to insert TEST 2 to hashmap\n\x1b[0m") & 0);
	if (!ft_hmap_insert(hashmap, "test3", test3()))
		return (ft_dprintf(2, "\x1b[31m[ERROR]: Failed to insert TEST 3 to hashmap\n\x1b[0m") & 0);
	if (!ft_hmap_insert(hashmap, "test4", test4()))
		return (ft_dprintf(2, "\x1b[31m[ERROR]: Failed to insert TEST 4 to hashmap\n\x1b[0m") & 0);
	if (!ft_hmap_insert(hashmap, "test5", test5()))
		return (ft_dprintf(2, "\x1b[31m[ERROR]: Failed to insert TEST 5 to hashmap\n\x1b[0m") & 0);
	if (!ft_hmap_insert(hashmap, "test6", test6()))
		return (ft_dprintf(2, "\x1b[31m[ERROR]: Failed to insert TEST 6 to hashmap\n\x1b[0m") & 0);
	if (!ft_hmap_insert(hashmap, "test7", test7()))
		return (ft_dprintf(2, "\x1b[31m[ERROR]: Failed to insert TEST 7 to hashmap\n\x1b[0m") & 0);

	/*		test 8 et A 		*/

	if (!ft_hmap_insert(hashmap, "testB", test_b()))
		return (ft_dprintf(2, "\x1b[31m[ERROR]: Failed to insert TEST B to hashmap\n\x1b[0m") & 0);
	if (!ft_hmap_insert(hashmap, "testC", test_c()))
		return (ft_dprintf(2, "\x1b[31m[ERROR]: Failed to insert TEST C to hashmap\n\x1b[0m") & 0);
	if (!ft_hmap_insert(hashmap, "testD", test_d()))
		return (ft_dprintf(2, "\x1b[31m[ERROR]: Failed to insert TEST D to hashmap\n\x1b[0m") & 0);
	if (!ft_hmap_insert(hashmap, "testE", test_e()))
		return (ft_dprintf(2, "\x1b[31m[ERROR]: Failed to insert TEST E to hashmap\n\x1b[0m") & 0);
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
	if (!ft_strcmp(test, "testF"))
		return (EXEC_TEST_F);
	if (!ft_strcmp(test, "testG"))
		return (EXEC_TEST_G);
	return	(NULL);
}
