/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 13:26:12 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/09 16:30:26 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unit.h"

void	print_header(void)
{
	ft_printf("\n  -------------------TEST RESULTS-------------------\n");
}

void	print_separator(void)
{
	ft_printf("  --------------------------------------------------\n");
}

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
	print_header();
	test_virt_registry();
	print_separator();

	test_null_value();
	print_separator();

	test_clipboard();
	print_separator();

	test_arrow_keys();
	print_separator();

	test_insertion();
	print_separator();

	test_deletion();
	print_separator();

	test_wjump();
	print_separator();

	return (result);
}
