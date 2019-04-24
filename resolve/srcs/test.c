/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 10:30:27 by nrechati          #+#    #+#             */
/*   Updated: 2019/04/24 10:11:22 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "resolve.h"
#include "reso.h"

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
	if (!ft_hmap_insert(hashmap, "test8", test8()))
		return (ft_dprintf(2, "\x1b[31m[ERROR]: Failed to insert TEST 8 to hashmap\n\x1b[0m") & 0);
	return (1);
}

int		setup_job(t_job *job, char *test)
{

	if (!ft_strcmp(test, "test1"))
		init_job1(job);
	if (!ft_strcmp(test, "test2"))
		init_job2(job);
	if (!ft_strcmp(test, "test3"))
		init_job3(job);
	if (!ft_strcmp(test, "test4"))
		init_job4(job);
	if (!ft_strcmp(test, "test5"))
		init_job5(job);
	if (!ft_strcmp(test, "test6"))
		init_job6(job);
	if (!ft_strcmp(test, "test7"))
		init_job7(job);
	if (!ft_strcmp(test, "test8"))
		init_job8(job);
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
	return	(NULL);
}
