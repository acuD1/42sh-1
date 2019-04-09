/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrows.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 15:47:49 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/09 15:28:15 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unit.h"

int	test_aw_left_easy(void)
{
	t_registry *sh;
	t_interface_registry *itf;
	if (create_virtual_registry(&sh, &itf) != 0)
		return (FALSE);

	itf->window->cursor_index = 16;
	itf->window->x = ft_strlen(itf->interface_state) + 16;
	itf->window->y = 0;

	ft_strcpy(itf->vector->buffer, "01234567890123456789");
	itf->window->cursor_index = tc_ak_arrow_left(itf);
	itf->window->cursor_index = tc_ak_arrow_left(itf);
	itf->window->cursor_index = tc_ak_arrow_left(itf);
	if (itf->window->cursor_index != 13
		|| itf->window->x != ft_strlen(itf->interface_state) + 13
		|| itf->window->y != 0)
		return (FALSE);

	itf->window->cursor_index = tc_ak_arrow_right(itf);
	itf->window->cursor_index = tc_ak_arrow_right(itf);
	itf->window->cursor_index = tc_ak_arrow_right(itf);

	return (TRUE);
}
int	test_aw_right_easy(void)
{
	t_registry *sh;
	t_interface_registry *itf;
	if (create_virtual_registry(&sh, &itf) != 0)
		return (FALSE);

	itf->window->cursor_index = 16;
	itf->window->x = ft_strlen(itf->interface_state) + 16;
	itf->window->y = 0;

	ft_strcpy(itf->vector->buffer, "01234567890123456789");
	itf->window->cursor_index = tc_ak_arrow_right(itf);
	itf->window->cursor_index = tc_ak_arrow_right(itf);
	itf->window->cursor_index = tc_ak_arrow_right(itf);
	if (itf->window->cursor_index != 19
		|| itf->window->x != ft_strlen(itf->interface_state) + 19
		|| itf->window->y != 0)
		return (FALSE);
	itf->window->cursor_index = tc_ak_arrow_left(itf);
	itf->window->cursor_index = tc_ak_arrow_left(itf);
	itf->window->cursor_index = tc_ak_arrow_left(itf);

	return (TRUE);
}

int	test_aw_right_multiline(void)
{
	t_registry *sh;
	t_interface_registry *itf;
	if (create_virtual_registry(&sh, &itf) != 0)
		return (FALSE);

	itf->vector = ft_vctnew(64);
	itf->window->cols = 32;
	itf->window->cursor_index = 16;
	itf->window->x = ft_strlen(itf->interface_state) + 16;
	itf->window->y = 0;

	// 60chars
ft_memset(itf->vector->buffer, 65, 60);

	for (int i = 0; i < 28; i++)
		itf->window->cursor_index = tc_ak_arrow_right(itf);

	if (itf->window->cursor_index != (16 + 28)
		|| itf->window->x != ft_strlen(itf->interface_state) + (12)
		|| itf->window->y != 1)
		return (FALSE);

	for (int i = 0; i < 28; i++)
		itf->window->cursor_index = tc_ak_arrow_left(itf);

	return (TRUE);
}
int	test_aw_left_multiline(void)
{
	t_registry *sh;
	t_interface_registry *itf;
	if (create_virtual_registry(&sh, &itf) != 0)
		return (FALSE);

	itf->vector = ft_vctnew(128);
	itf->window->cols = 32;
	itf->window->rows = 32;
	itf->window->cursor_index = 127;

	// 128chars
	ft_memset(itf->vector->buffer, 65, 127);
	for (int i = 0; i < 40; i++)
		itf->window->cursor_index = tc_ak_arrow_left(itf);
	if (itf->window->cursor_index != (127 - 40))
		return (FALSE);
	return (TRUE);
}

int test_home(void)
{
	t_registry *sh;
	t_interface_registry *itf;
	if (create_virtual_registry(&sh, &itf) != 0)
		return (FALSE);

	itf->vector = ft_vctnew(128);
	itf->window->cols = 32;
	itf->window->rows = 32;
	itf->window->cursor_index = 127;
	itf->window->y = 3;
	itf->window->x = 31;
	ft_memset(itf->vector->buffer, 65, itf->vector->size - 2);

	itf->window->cursor_index = tc_ak_home(itf);
	if (itf->window->cursor_index != 0
		|| itf->window->y != 0)
		return (FALSE);
	itf->window->cursor_index = tc_ak_end(itf);

	return (TRUE);
}

int test_end(void)
{
	t_registry *sh;
	t_interface_registry *itf;
	if (create_virtual_registry(&sh, &itf) != 0)
		return (FALSE);

	itf->vector = ft_vctnew(128);
	itf->window->cols = 32;
	itf->window->rows = 32;
	itf->window->cursor_index = 0;
	ft_memset(itf->vector->buffer, 65, itf->vector->size - 2);
	itf->window->y = 0;

	itf->window->cursor_index = tc_ak_end(itf);
	if (itf->window->cursor_index == 0
			|| itf->window->y == 0)
		return (FALSE);
	itf->window->cursor_index = tc_ak_home(itf);

	return (TRUE);
}

int test_arrow_keys(void)
{
	t_stack tests;

	ft_stckinit(&tests);
	load_test(&tests, "End ", test_end);
	load_test(&tests, "Home ", test_home);

	load_test(&tests, "Multiline left", test_aw_left_multiline);
	load_test(&tests, "Multiline right", test_aw_right_multiline);

	load_test(&tests, "Left ak test easy", test_aw_left_easy);
	load_test(&tests, "Right ak test easy", test_aw_right_easy);

	return (run_test(&tests));
}
