/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_jump.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 16:19:27 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/09 16:51:07 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unit.h"

void copy_lorem_to_buffer(t_vector *t, size_t length)
{
	char *lorem_ipsum = "Lorems ipsum dolor sit amet, cls";
	t->buffer = ft_strnew(length + 1);
	t->size = length + 1;
	ft_strncpy(t->buffer, lorem_ipsum, length + 1);
}

int	test_next_word_easy(void)
{
	t_registry *sh;
	t_interface_registry *itf;
	if (create_virtual_registry(&sh, &itf) != 0)
		return (FALSE);
	copy_lorem_to_buffer(itf->vector, 32);
//	ft_printf("x: %s| s:%d\n", itf->vector->buffer,ft_strlen(itf->vector->buffer));
	itf->window->cursor_index = 0;
	itf->window->cursor_index = tc_ak_next_word(itf);

	if (itf->vector->buffer[itf->window->cursor_index] != 'i'
		|| itf->window->cursor_index != 7)
		return (FALSE);
	itf->window->cursor_index = tc_ak_prev_word(itf);
	return (TRUE);
}

int	test_next_word_medium(void)
{
	t_registry *sh;
	t_interface_registry *itf;
	if (create_virtual_registry(&sh, &itf) != 0)
		return (FALSE);

	copy_lorem_to_buffer(itf->vector, 32);
	itf->window->cursor_index = 0;
	itf->window->cursor_index = tc_ak_next_word(itf);
	itf->window->cursor_index = tc_ak_next_word(itf);
	itf->window->cursor_index = tc_ak_next_word(itf);

	if (itf->vector->buffer[itf->window->cursor_index] != 's'
		|| itf->window->cursor_index != 19)
		return (FALSE);
	itf->window->cursor_index = tc_ak_prev_word(itf);
	itf->window->cursor_index = tc_ak_prev_word(itf);
	itf->window->cursor_index = tc_ak_prev_word(itf);
	return (TRUE);
}

int	test_prev_word_easy(void)
{
	t_registry *sh;
	t_interface_registry *itf;
	if (create_virtual_registry(&sh, &itf) != 0)
		return (FALSE);

	copy_lorem_to_buffer(itf->vector, 32);
	itf->window->cursor_index = 27;
	itf->window->cursor_index = tc_ak_prev_word(itf);

	if (itf->vector->buffer[itf->window->cursor_index] != 's'
		|| itf->window->cursor_index != 19)
		return (FALSE);
	return (TRUE);
}

int	test_prev_word_medium(void)
{
	t_registry *sh;
	t_interface_registry *itf;
	if (create_virtual_registry(&sh, &itf) != 0)
		return (FALSE);

	copy_lorem_to_buffer(itf->vector, 32);
	itf->window->cursor_index = 32;
	itf->window->cursor_index = tc_ak_prev_word(itf);
	itf->window->cursor_index = tc_ak_prev_word(itf);
	itf->window->cursor_index = tc_ak_prev_word(itf);

	if (itf->vector->buffer[itf->window->cursor_index] != 'd'
		|| itf->window->cursor_index != 13)
		return (FALSE);
	return (TRUE);
}
int	test_prev_word_edge(void)
{
	t_registry *sh;
	t_interface_registry *itf;
	if (create_virtual_registry(&sh, &itf) != 0)
		return (FALSE);

	copy_lorem_to_buffer(itf->vector, 32);
	itf->window->cursor_index = 7;
	itf->window->cursor_index = tc_ak_prev_word(itf);
	itf->window->cursor_index = tc_ak_prev_word(itf);

	if (itf->vector->buffer[itf->window->cursor_index] != 'L'
		|| itf->window->cursor_index != 0)
		return (FALSE);
	return (TRUE);
}
int	test_next_word_edge(void)
{
	t_registry *sh;
	t_interface_registry *itf;
	if (create_virtual_registry(&sh, &itf) != 0)
		return (FALSE);

	copy_lorem_to_buffer(itf->vector, 32);
	itf->window->cursor_index = 25;
	itf->window->cursor_index = tc_ak_prev_word(itf);
	itf->window->cursor_index = tc_ak_prev_word(itf);

	if (itf->vector->buffer[itf->window->cursor_index] != 'c'
		|| itf->window->cursor_index != 29)
		return (FALSE);
	return (TRUE);
}

int	test_wjump()
{
	t_stack tests;
	ft_stckinit(&tests);

	load_test(&tests, "Test prev word edge		|", test_prev_word_edge);
	load_test(&tests, "Test next word edge		|", test_next_word_edge);

	load_test(&tests, "Test prev word easy		|", test_prev_word_easy);
	load_test(&tests, "Test prev word medium	|", test_prev_word_medium);

	load_test(&tests, "Test next word easy		|", test_next_word_easy);
	load_test(&tests, "Test next word medium	|", test_next_word_medium);


	return (run_test(&tests));
}
