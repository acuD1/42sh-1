/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_delete.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 15:31:43 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/09 19:22:03 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unit.h"

int test_insert_easy(void)
{
	t_registry *sh;
	t_interface_registry *itf;
	if (create_virtual_registry(&sh, &itf) != 0)
		return (FALSE);

	itf->line = ft_vctnew(4);
	itf->window->cursor = 0;

	handle_printable_char('x', itf);
	if (!ft_strequ("x", itf->line->buffer) || itf->window->cursor != 1)
		return (FALSE);
	return (TRUE);
}
int test_insert_append(void)
{
	t_registry *sh;
	t_interface_registry *itf;
	if (create_virtual_registry(&sh, &itf) != 0)
		return (FALSE);

	itf->line = ft_vctnew(8);
	itf->window->cursor = 3;
	ft_memset(itf->line->buffer, 97, 3);

	handle_printable_char('x', itf);
	if (!ft_strequ("aaax", itf->line->buffer) || itf->window->cursor != 4)
		return (FALSE);
	return (TRUE);
}
int test_insert_between(void)
{
	t_registry *sh;
	t_interface_registry *itf;
	if (create_virtual_registry(&sh, &itf) != 0)
		return (FALSE);

	itf->line = ft_vctnew(8);
	itf->window->cursor = 4;
	ft_memset(itf->line->buffer, 97, 7);

	handle_printable_char('x', itf);
	if (!ft_strequ("aaaaxaaa", itf->line->buffer) || itf->window->cursor != 5)
		return (FALSE);
	return (TRUE);
}
int test_insert_start(void)
{
	t_registry *sh;
	t_interface_registry *itf;
	if (create_virtual_registry(&sh, &itf) != 0)
		return (FALSE);

	itf->line = ft_vctnew(8);
	itf->window->cursor = 0;
	ft_memset(itf->line->buffer, 97, 6);

	handle_printable_char('x', itf);
	if (!ft_strequ("xaaaaaa", itf->line->buffer) || itf->window->cursor != 1)
		return (FALSE);
	return (TRUE);
}



int test_insertion(void)
{
	t_stack tests;
	ft_stckinit(&tests);

	load_test(&tests, "Insertion easy", test_insert_easy);
	load_test(&tests, "Insertion start", test_insert_start);
	load_test(&tests, "Insertion end", test_insert_append);
	load_test(&tests, "Insertion between", test_insert_between);


	return (run_test(&tests));
}

int test_delete_easy(void)
{
	t_registry *sh;
	t_interface_registry *itf;
	if (create_virtual_registry(&sh, &itf) != 0)
		return (FALSE);

	itf->line = ft_vctnew(8);
	itf->window->cursor = 0;
	ft_memset(itf->line->buffer, 97, 4);

	tc_ak_delete(itf);
	if (!ft_strequ("aaa", itf->line->buffer) || itf->window->cursor != 0)
		return (FALSE);
	return (TRUE);
}

int test_delete_start(void)
{
	t_registry *sh;
	t_interface_registry *itf;
	if (create_virtual_registry(&sh, &itf) != 0)
		return (FALSE);

	itf->line = ft_vctnew(8);
	itf->window->cursor = 0;
	ft_memset(itf->line->buffer, 97, 4);

	tc_ak_delete(itf);
	if (!ft_strequ("aaa", itf->line->buffer) || itf->window->cursor != 0)
		return (FALSE);
	return (TRUE);
}

int test_delete_end(void)
{
	t_registry *sh;
	t_interface_registry *itf;
	if (create_virtual_registry(&sh, &itf) != 0)
		return (FALSE);

	itf->line = ft_vctnew(8);
	itf->window->cursor = 4;
	ft_memset(itf->line->buffer, 97, 4);

	tc_ak_delete(itf);
	if (!ft_strequ("aaaa", itf->line->buffer) || itf->window->cursor != 4)
		return (FALSE);
	return (TRUE);
}

int test_delete_between(void)
{
	t_registry *sh;
	t_interface_registry *itf;
	if (create_virtual_registry(&sh, &itf) != 0)
		return (FALSE);

	itf->line = ft_vctnew(8);
	itf->window->cursor = 2;
	ft_memset(itf->line->buffer, 97, 4);

	tc_ak_delete(itf);
	if (!ft_strequ("aaa", itf->line->buffer) || itf->window->cursor != 2)
		return (FALSE);
	return (TRUE);
}

int test_backspace_easy(void)
{
	t_registry *sh;
	t_interface_registry *itf;
	if (create_virtual_registry(&sh, &itf) != 0)
		return (FALSE);

	itf->line = ft_vctnew(8);
	itf->window->cursor = 1;
	ft_memset(itf->line->buffer, 97, 4);

	tc_ak_backspace(itf);
	if (!ft_strequ("aaa", itf->line->buffer) || itf->window->cursor != 0)
		return (FALSE);
	return (TRUE);
}

int test_backspace_start(void)
{
	t_registry *sh;
	t_interface_registry *itf;
	if (create_virtual_registry(&sh, &itf) != 0)
		return (FALSE);

	itf->line = ft_vctnew(8);
	itf->window->cursor = 0;
	ft_memset(itf->line->buffer, 97, 4);

	tc_ak_backspace(itf);
	if (!ft_strequ("aaaa", itf->line->buffer) || itf->window->cursor != 0)
		return (FALSE);
	return (TRUE);
}

int test_backspace_end(void)
{
	t_registry *sh;
	t_interface_registry *itf;
	if (create_virtual_registry(&sh, &itf) != 0)
		return (FALSE);

	itf->line = ft_vctnew(8);
	itf->window->cursor = 4;
	ft_memset(itf->line->buffer, 97, 4);

	tc_ak_backspace(itf);
	if (!ft_strequ("aaa", itf->line->buffer) || itf->window->cursor != 3)
		return (FALSE);
	return (TRUE);
}

int test_backspace_between(void)
{
	t_registry *sh;
	t_interface_registry *itf;
	if (create_virtual_registry(&sh, &itf) != 0)
		return (FALSE);

	itf->line = ft_vctnew(8);
	itf->window->cursor = 2;
	ft_memset(itf->line->buffer, 97, 4);

	tc_ak_backspace(itf);
	if (!ft_strequ("aaa", itf->line->buffer) || itf->window->cursor != 1)
		return (FALSE);
	return (TRUE);
}


int test_deletion(void)
{
	t_stack tests;
	ft_stckinit(&tests);

	load_test(&tests, "Delete end			|", test_delete_end);
	load_test(&tests, "Delete between		|", test_delete_between);
	load_test(&tests, "Delete start			|", test_delete_start);
	load_test(&tests, "Delete easy			|", test_delete_easy);

	load_test(&tests, "Backspace end			|", test_backspace_end);
	load_test(&tests, "Backspace between		|", test_backspace_between);
	load_test(&tests, "Backspace start		|", test_backspace_start);
	load_test(&tests, "Backspace easy		|", test_backspace_easy);

	return (run_test(&tests));
}
