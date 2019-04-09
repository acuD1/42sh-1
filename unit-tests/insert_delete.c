/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_delete.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 15:31:43 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/09 16:02:54 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unit.h"

int test_insert_easy(void)
{
	t_registry *sh;
	t_interface_registry *itf;
	if (create_virtual_registry(&sh, &itf) != 0)
		return (FALSE);

	itf->vector = ft_vctnew(4);
	itf->window->cursor_index = 0;

	handle_printable_char('x', itf);
	if (!ft_strequ("x", itf->vector->buffer) || itf->window->cursor_index != 1)
		return (FALSE);
	return (TRUE);
}
int test_insert_append(void)
{
	t_registry *sh;
	t_interface_registry *itf;
	if (create_virtual_registry(&sh, &itf) != 0)
		return (FALSE);

	itf->vector = ft_vctnew(8);
	itf->window->cursor_index = 3;
	ft_memset(itf->vector->buffer, 97, 3);

	handle_printable_char('x', itf);
	if (!ft_strequ("aaax", itf->vector->buffer) || itf->window->cursor_index != 4)
		return (FALSE);
	return (TRUE);
}
int test_insert_between(void)
{
	t_registry *sh;
	t_interface_registry *itf;
	if (create_virtual_registry(&sh, &itf) != 0)
		return (FALSE);

	itf->vector = ft_vctnew(8);
	itf->window->cursor_index = 4;
	ft_memset(itf->vector->buffer, 97, 7);

	handle_printable_char('x', itf);
	if (!ft_strequ("aaaaxaaa", itf->vector->buffer) || itf->window->cursor_index != 5)
		return (FALSE);
	return (TRUE);
}
int test_insert_start(void)
{
	t_registry *sh;
	t_interface_registry *itf;
	if (create_virtual_registry(&sh, &itf) != 0)
		return (FALSE);

	itf->vector = ft_vctnew(8);
	itf->window->cursor_index = 0;
	ft_memset(itf->vector->buffer, 97, 6);

	handle_printable_char('x', itf);
	if (!ft_strequ("xaaaaaa", itf->vector->buffer) || itf->window->cursor_index != 1)
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

	itf->vector = ft_vctnew(8);
	itf->window->cursor_index = 0;
	ft_memset(itf->vector->buffer, 97, 4);

	tc_ak_delete(itf);
	if (!ft_strequ("aaa", itf->vector->buffer) || itf->window->cursor_index != 0)
		return (FALSE);
	return (TRUE);
}

int test_delete_start(void)
{
	t_registry *sh;
	t_interface_registry *itf;
	if (create_virtual_registry(&sh, &itf) != 0)
		return (FALSE);

	itf->vector = ft_vctnew(8);
	itf->window->cursor_index = 0;
	ft_memset(itf->vector->buffer, 97, 4);

	tc_ak_delete(itf);
	if (!ft_strequ("aaa", itf->vector->buffer) || itf->window->cursor_index != 0)
		return (FALSE);
	return (TRUE);
}

int test_delete_end(void)
{
	t_registry *sh;
	t_interface_registry *itf;
	if (create_virtual_registry(&sh, &itf) != 0)
		return (FALSE);

	itf->vector = ft_vctnew(8);
	itf->window->cursor_index = 0;
	ft_memset(itf->vector->buffer, 97, 4);

	tc_ak_delete(itf);
	if (!ft_strequ("aaa", itf->vector->buffer) || itf->window->cursor_index != 0)
		return (FALSE);
	return (TRUE);
}

int test_delete_between(void)
{
	t_registry *sh;
	t_interface_registry *itf;
	if (create_virtual_registry(&sh, &itf) != 0)
		return (FALSE);

	itf->vector = ft_vctnew(8);
	itf->window->cursor_index = 0;
	ft_memset(itf->vector->buffer, 97, 4);

	tc_ak_delete(itf);
	if (!ft_strequ("aaa", itf->vector->buffer) || itf->window->cursor_index != 0)
		return (FALSE);
	return (TRUE);

}

int test_backspace_easy(void)
{


}

int test_backspace_start(void)
{

}

int test_backspace_end(void)
{


}

int test_backspace_between(void)
{

}


int test_deletion()
{
	t_stack tests;
	ft_stckinit(&tests);

	load_test(&tests, "Delete easy", test_delete_easy);
	load_test(&tests, "Delete start", test_delete_start);
	load_test(&tests, "Delete end", test_delete_end);
	load_test(&tests, "Delete between", test_delete_between);

	load_test(&tests, "Backspace easy", test_backspace_easy);
	load_test(&tests, "Backspace start", test_backspace_start);
	load_test(&tests, "Backspace end", test_backspace_end);
	load_test(&tests, "Backspace between", test_backspace_between);

	return (run_test(&tests));
}
