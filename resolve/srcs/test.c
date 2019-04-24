/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 10:30:27 by nrechati          #+#    #+#             */
/*   Updated: 2019/04/24 14:31:31 by nrechati         ###   ########.fr       */
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
	if (!ft_hmap_insert(hashmap, "test9", test9()))
		return (ft_dprintf(2, "\x1b[31m[ERROR]: Failed to insert TEST 9 to hashmap\n\x1b[0m") & 0);
	if (!ft_hmap_insert(hashmap, "testA", test_a()))
		return (ft_dprintf(2, "\x1b[31m[ERROR]: Failed to insert TEST A to hashmap\n\x1b[0m") & 0);
	if (!ft_hmap_insert(hashmap, "testB", test_b()))
		return (ft_dprintf(2, "\x1b[31m[ERROR]: Failed to insert TEST B to hashmap\n\x1b[0m") & 0);
	if (!ft_hmap_insert(hashmap, "testC", test_c()))
		return (ft_dprintf(2, "\x1b[31m[ERROR]: Failed to insert TEST C to hashmap\n\x1b[0m") & 0);
	if (!ft_hmap_insert(hashmap, "testD", test_d()))
		return (ft_dprintf(2, "\x1b[31m[ERROR]: Failed to insert TEST D to hashmap\n\x1b[0m") & 0);
	if (!ft_hmap_insert(hashmap, "testE", test_e()))
		return (ft_dprintf(2, "\x1b[31m[ERROR]: Failed to insert TEST E to hashmap\n\x1b[0m") & 0);
	if (!ft_hmap_insert(hashmap, "testF", test_f()))
		return (ft_dprintf(2, "\x1b[31m[ERROR]: Failed to insert TEST F to hashmap\n\x1b[0m") & 0);
	if (!ft_hmap_insert(hashmap, "testG", test_g()))
		return (ft_dprintf(2, "\x1b[31m[ERROR]: Failed to insert TEST G to hashmap\n\x1b[0m") & 0);

//	if (!ft_hmap_insert(hashmap, "testH", test_h()))
//		return (ft_dprintf(2, "\x1b[31m[ERROR]: Failed to insert TEST H to hashmap\n\x1b[0m") & 0);
//	if (!ft_hmap_insert(hashmap, "testI", test_i()))
//		return (ft_dprintf(2, "\x1b[31m[ERROR]: Failed to insert TEST I to hashmap\n\x1b[0m") & 0);
//	if (!ft_hmap_insert(hashmap, "testJ", test_j()))
//		return (ft_dprintf(2, "\x1b[31m[ERROR]: Failed to insert TEST J to hashmap\n\x1b[0m") & 0);
//	if (!ft_hmap_insert(hashmap, "testK", test_k()))
//		return (ft_dprintf(2, "\x1b[31m[ERROR]: Failed to insert TEST K to hashmap\n\x1b[0m") & 0);
//	if (!ft_hmap_insert(hashmap, "testL", test_l()))
//		return (ft_dprintf(2, "\x1b[31m[ERROR]: Failed to insert TEST L to hashmap\n\x1b[0m") & 0);
//	if (!ft_hmap_insert(hashmap, "testM", test_m()))
//		return (ft_dprintf(2, "\x1b[31m[ERROR]: Failed to insert TEST M to hashmap\n\x1b[0m") & 0);
//	if (!ft_hmap_insert(hashmap, "testN", test_n()))
//		return (ft_dprintf(2, "\x1b[31m[ERROR]: Failed to insert TEST N to hashmap\n\x1b[0m") & 0);
//	if (!ft_hmap_insert(hashmap, "testO", test_o()))
//		return (ft_dprintf(2, "\x1b[31m[ERROR]: Failed to insert TEST O to hashmap\n\x1b[0m") & 0);
//	if (!ft_hmap_insert(hashmap, "testP", test_p()))
//		return (ft_dprintf(2, "\x1b[31m[ERROR]: Failed to insert TEST P to hashmap\n\x1b[0m") & 0);

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
	if (!ft_strcmp(test, "test9"))
		init_job9(job);
	if (!ft_strcmp(test, "testA"))
		init_job_a(job);
	if (!ft_strcmp(test, "testB"))
		init_job_b(job);
	if (!ft_strcmp(test, "testC"))
		init_job_c(job);
	if (!ft_strcmp(test, "testD"))
		init_job_d(job);
	if (!ft_strcmp(test, "testE"))
		init_job_e(job);
	if (!ft_strcmp(test, "testF"))
		init_job_f(job);
	if (!ft_strcmp(test, "testG"))
		init_job_g(job);

//	if (!ft_strcmp(test, "testH"))
//		init_job_h(job);
//	if (!ft_strcmp(test, "testI"))
//		init_job_i(job);
//	if (!ft_strcmp(test, "testJ"))
//		init_job_j(job);
//	if (!ft_strcmp(test, "testK"))
//		init_job_k(job);
//	if (!ft_strcmp(test, "testL"))
//		init_job_l(job);
//	if (!ft_strcmp(test, "testM"))
//		init_job_m(job);
//	if (!ft_strcmp(test, "testN"))
//		init_job_n(job);
//	if (!ft_strcmp(test, "testO"))
//		init_job_o(job);
//	if (!ft_strcmp(test, "testP"))
//		init_job_p(job);
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
	if (!ft_strcmp(test, "test9"))
		return (EXEC_TEST_9);
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
	if (!ft_strcmp(test, "testH"))
		return (EXEC_TEST_I);
	if (!ft_strcmp(test, "testI"))
		return (EXEC_TEST_J);
	if (!ft_strcmp(test, "testJ"))
		return (EXEC_TEST_K);
	if (!ft_strcmp(test, "testK"))
		return (EXEC_TEST_B);
	return	(NULL);
}
