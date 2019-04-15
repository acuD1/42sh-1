/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 13:26:12 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/15 19:19:58 by skuppers         ###   ########.fr       */
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

void		interface(int print_on)
{
	t_list	*results;

	results = NULL;
	print_test_header();
	set_test(&results, test_virt_registry(print_on));
	print_test_separator(print_on);
	set_test(&results, test_clipboard_copy(print_on));
	print_test_separator(print_on);
	set_test(&results, test_clipboard_cut(print_on));
	print_test_separator(print_on);
	set_test(&results, test_clipboard_paste(print_on));
	print_test_separator(print_on);
	return ;
}

int main(int ac, char **av)
{
	int		print_on;

	print_on = 0;
	if (ac > 1)
	{
		if (ft_strequ(av[1], "-v"))
			print_on++;
	}
	interface(print_on);
	return (0);
}
