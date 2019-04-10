/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 13:26:12 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/10 15:21:07 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unit.h"

void gen_test_dir(void)
{
	int fd;

	mkdir("./21sh_tests/", T_CHMOD);
	fd = open("./21sh_tests/exec", O_CREAT | O_TRUNC);
	close(fd);
}

int main(void)
{
	int result;

	result = 0;

	print_test_header();
	test_virt_registry();
	print_test_separator();
	test_null_value();
	print_test_separator();
	test_clipboard();
	print_test_separator();
	test_arrow_keys();
	print_test_separator();
	test_insertion();
	print_test_separator();
	test_deletion();
	print_test_separator();
	test_wjump();
	print_test_separator();
	return (result);
}
