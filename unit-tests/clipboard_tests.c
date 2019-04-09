/*                                                        :::      ::::::::   */
/*   clipboard_tests.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 13:45:36 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/03 18:02:05 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unit.h"

static int test_copy_bf(void)
{
	t_registry *sh;
	t_interface_registry *itf;
	if (create_virtual_registry(&sh, &itf) != 0)
		return (FALSE);

	size_t c_pos = 0;
	itf->window->cursor_index = 0;
	c_pos = tc_ak_copy_before_cursor((itf));
	if (c_pos != 0)
		return (FALSE);
	if (!ft_strequ(itf->clipboard->buffer, ""))
		return (FALSE);
	return (TRUE);
}

static int test_copy_bf1(void)
{
	t_registry *sh;
	t_interface_registry *itf;
	if (create_virtual_registry(&sh, &itf) != 0)
		return (FALSE);

	size_t c_pos = 0;
	itf->window->cursor_index = 1;

	ft_strcpy(itf->vector->buffer, "a");

	c_pos = tc_ak_copy_before_cursor((itf));
	if (c_pos != 1)
		return (FALSE);
	if (!ft_strequ(itf->clipboard->buffer, itf->vector->buffer))
		return (FALSE);
	return (TRUE);
}
static int test_copy_bf32(void)
{
	t_registry *sh;
	t_interface_registry *itf;
	if (create_virtual_registry(&sh, &itf) != 0)
		return (FALSE);

	size_t c_pos = 0;
	itf->window->cursor_index = 11;

	ft_strcpy(itf->vector->buffer, "x012345678901234567890123456789x");

	c_pos = tc_ak_copy_before_cursor((itf));
	if (c_pos != 11)
		return (FALSE);
	if (!ft_strequ(itf->clipboard->buffer, "x0123456789") || !ft_strequ(itf->vector->buffer, "x012345678901234567890123456789x"))
		return (FALSE);
	return (TRUE);
}
static int test_copy_bf33(void)
{
	t_registry *sh;
	t_interface_registry *itf;
	if (create_virtual_registry(&sh, &itf) != 0)
		return (FALSE);

	size_t c_pos = 0;
	itf->window->cursor_index = 33;

	ft_strcpy(itf->vector->buffer, "x012345678901234567890123456789xx");

	c_pos = tc_ak_copy_before_cursor((itf));
	if (c_pos != 33)
		return (FALSE);
	if (!ft_strequ(itf->clipboard->buffer, itf->vector->buffer))
		return (FALSE);
	return (TRUE);
}
static int test_copy_bf512(void)
{
	t_registry *sh;
	t_interface_registry *itf;
	if (create_virtual_registry(&sh, &itf) != 0)
		return (FALSE);

	size_t c_pos = 0;
	itf->window->cursor_index = 128;

	itf->vector = ft_vctnew(512);
	ft_strcpy(itf->vector->buffer, "Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Aenean commodo ligula eget dolor. Aenean massa. Cum sociis natoque penatibus et magnis dis parturient montes, nascetur ridiculus mus. Donec quam felis, ultricies nec, pellentesque eu, pretium quis, sem. Nulla consequat massa quis enim. Donec pede justo, fringilla vel, aliquet nec, vulputate eget, arcu. In enim justo, rhoncus ut, imperdiet a, venenatis vitae, justo. Nullam dictum felis eu pede mollis pretium. Integer tincidunt. Cras dapibus. Vivamus e");

	c_pos = tc_ak_copy_before_cursor((itf));
	if (c_pos != 128)
		return (FALSE);
	if (!ft_strequ(itf->clipboard->buffer, "Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Aenean commodo ligula eget dolor. Aenean massa. Cum sociis natoque pen"))
		return (FALSE);
	return (TRUE);
}
// -----------------------------------------------------------------------------

static int test_copy_af(void)
{
	t_registry *sh;
	t_interface_registry *itf;
	if (create_virtual_registry(&sh, &itf) != 0)
		return (FALSE);

	size_t c_pos = 0;
	itf->window->cursor_index = 0;
	c_pos = tc_ak_copy_after_cursor((itf));
	if (c_pos != 0)
		return (FALSE);
	if (!ft_strequ(itf->clipboard->buffer, ""))
		return (FALSE);
	return (TRUE);
}

static int test_copy_af1(void)
{
	t_registry *sh;
	t_interface_registry *itf;
	if (create_virtual_registry(&sh, &itf) != 0)
		return (FALSE);

	size_t c_pos = 0;
	itf->window->cursor_index = 1;

	ft_strcpy(itf->vector->buffer, "a");

	c_pos = tc_ak_copy_after_cursor((itf));
	if (c_pos != 1)
		return (FALSE);
	if (!ft_strequ(itf->clipboard->buffer, "") || !ft_strequ(itf->vector->buffer, "a"))
		return (FALSE);
	return (TRUE);
}
static int test_copy_af32(void)
{
	t_registry *sh;
	t_interface_registry *itf;
	if (create_virtual_registry(&sh, &itf) != 0)
		return (FALSE);

	size_t c_pos = 0;
	itf->window->cursor_index = 11;

	ft_strcpy(itf->vector->buffer, "x012345678901234567890123456789x");

	c_pos = tc_ak_copy_after_cursor((itf));
	if (c_pos != 11)
		return (FALSE);
	if (!ft_strequ(itf->clipboard->buffer, "01234567890123456789x") || !ft_strequ(itf->vector->buffer, "x012345678901234567890123456789x"))
		return (FALSE);
	return (TRUE);
}
static int test_copy_af33(void)
{
	t_registry *sh;
	t_interface_registry *itf;
	if (create_virtual_registry(&sh, &itf) != 0)
		return (FALSE);

	size_t c_pos = 0;
	itf->window->cursor_index = 33;

	ft_strcpy(itf->vector->buffer, "x012345678901234567890123456789xx");

	c_pos = tc_ak_copy_after_cursor((itf));
	if (c_pos != 33)
		return (FALSE);
	if (!ft_strequ(itf->clipboard->buffer, "") || !ft_strequ(itf->vector->buffer, "x012345678901234567890123456789xx"))
		return (FALSE);
	return (TRUE);
}
static int test_copy_af512(void)
{
	t_registry *sh;
	t_interface_registry *itf;
	if (create_virtual_registry(&sh, &itf) != 0)
		return (FALSE);

	size_t c_pos = 0;
	itf->window->cursor_index = 128;

	itf->vector = ft_vctnew(512);
	ft_strcpy(itf->vector->buffer, "Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Aenean commodo ligula eget dolor. Aenean massa. Cum sociis natoque penatibus et magnis dis parturient montes, nascetur ridiculus mus. Donec quam felis, ultricies nec, pellentesque eu, pretium quis, sem. Nulla consequat massa quis enim. Donec pede justo, fringilla vel, aliquet nec, vulputate eget, arcu. In enim justo, rhoncus ut, imperdiet a, venenatis vitae, justo. Nullam dictum felis eu pede mollis pretium. Integer tincidunt. Cras dapibus. Vivamus e");

	c_pos = tc_ak_copy_after_cursor((itf));
	if (c_pos != 128)
		return (FALSE);
	if (!ft_strequ(itf->clipboard->buffer, "atibus et magnis dis parturient montes, nascetur ridiculus mus. Donec quam felis, ultricies nec, pellentesque eu, pretium quis, sem. Nulla consequat massa quis enim. Donec pede justo, fringilla vel, aliquet nec, vulputate eget, arcu. In enim justo, rhoncus ut, imperdiet a, venenatis vitae, justo. Nullam dictum felis eu pede mollis pretium. Integer tincidunt. Cras dapibus. Vivamus e"))
		return (FALSE);
	return (TRUE);
}
// -----------------------------------------------------------------------------
static int test_copy(void)
{
	t_registry *sh;
	t_interface_registry *itf;
	if (create_virtual_registry(&sh, &itf) != 0)
		return (FALSE);

	size_t c_pos = 0;
	itf->window->cursor_index = 0;
	c_pos = tc_ak_copy_line(itf);
	if (c_pos != 0)
		return (FALSE);
	if (!ft_strequ(itf->clipboard->buffer, ""))
		return (FALSE);
	return (TRUE);
}

static int test_copy1(void)
{
	t_registry *sh;
	t_interface_registry *itf;
	if (create_virtual_registry(&sh, &itf) != 0)
		return (FALSE);

	size_t c_pos = 0;
	itf->window->cursor_index = 0;

	ft_strcpy(itf->vector->buffer, "a");

	c_pos = tc_ak_copy_line(itf);
	if (c_pos != 0)
		return (FALSE);
	if (!ft_strequ(itf->clipboard->buffer, "a") || !ft_strequ(itf->vector->buffer, "a"))
		return (FALSE);
	return (TRUE);
}
static int test_copy32(void)
{
	t_registry *sh;
	t_interface_registry *itf;
	if (create_virtual_registry(&sh, &itf) != 0)
		return (FALSE);

	size_t c_pos = 0;
	itf->window->cursor_index = 30;

	ft_strcpy(itf->vector->buffer, "x012345678901234567890123456789x");

	c_pos = tc_ak_copy_line(itf);
	if (c_pos != 30)
		return (FALSE);
	if (!ft_strequ(itf->clipboard->buffer, "x012345678901234567890123456789x") || !ft_strequ(itf->vector->buffer, "x012345678901234567890123456789x"))
		return (FALSE);
	return (TRUE);
}
static int test_copy33(void)
{
	t_registry *sh;
	t_interface_registry *itf;
	if (create_virtual_registry(&sh, &itf) != 0)
		return (FALSE);

	size_t c_pos = 0;
	itf->window->cursor_index = 33;

	ft_strcpy(itf->vector->buffer, "x012345678901234567890123456789xx");

	c_pos = tc_ak_copy_line(itf);
	if (c_pos != 33)
		return (FALSE);
	if (!ft_strequ(itf->clipboard->buffer, itf->vector->buffer))
		return (FALSE);
	return (TRUE);
}
static int test_copy512(void)
{
	t_registry *sh;
	t_interface_registry *itf;
	if (create_virtual_registry(&sh, &itf) != 0)
		return (FALSE);

	size_t c_pos = 0;
	itf->window->cursor_index = 128;

	itf->vector = ft_vctnew(512);
	ft_strcpy(itf->vector->buffer, "Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Aenean commodo ligula eget dolor. Aenean massa. Cum sociis natoque penatibus et magnis dis parturient montes, nascetur ridiculus mus. Donec quam felis, ultricies nec, pellentesque eu, pretium quis, sem. Nulla consequat massa quis enim. Donec pede justo, fringilla vel, aliquet nec, vulputate eget, arcu. In enim justo, rhoncus ut, imperdiet a, venenatis vitae, justo. Nullam dictum felis eu pede mollis pretium. Integer tincidunt. Cras dapibus. Vivamus e");

	c_pos = tc_ak_copy_line(itf);
	if (c_pos != 128)
		return (FALSE);
	if (!ft_strequ(itf->clipboard->buffer, itf->vector->buffer))
		return (FALSE);
	return (TRUE);
}
 // -------------------------------------------------------------------
static int test_cut(void)
{
	t_registry *sh;
	t_interface_registry *itf;
	if (create_virtual_registry(&sh, &itf) != 0)
		return (FALSE);

	itf->window->cursor_index = 0;


	prepare_clipboard(itf->clipboard, itf->vector);
	move_buffer(itf->clipboard->buffer, itf->vector);

	if (!ft_strequ(itf->clipboard->buffer, ""))
		return (FALSE);
	return (TRUE);
}

static int test_cut1(void)
{
	t_registry *sh;
	t_interface_registry *itf;
	if (create_virtual_registry(&sh, &itf) != 0)
		return (FALSE);

	itf->window->cursor_index = 0;
	ft_strcpy(itf->vector->buffer, "a");

	prepare_clipboard(itf->clipboard, itf->vector);
	move_buffer(itf->clipboard->buffer, itf->vector);

	if (!ft_strequ(itf->clipboard->buffer, "a") || !ft_strequ(itf->vector->buffer, ""))
		return (FALSE);
	return (TRUE);
}
static int test_cut32(void)
{
	t_registry *sh;
	t_interface_registry *itf;
	if (create_virtual_registry(&sh, &itf) != 0)
		return (FALSE);

	itf->window->cursor_index = 32;
	ft_strcpy(itf->vector->buffer, "x012345678901234567890123456789x");

	prepare_clipboard(itf->clipboard, itf->vector);
	move_buffer(itf->clipboard->buffer, itf->vector);

	if (!ft_strequ(itf->clipboard->buffer, "x012345678901234567890123456789x") || !ft_strequ(itf->vector->buffer, ""))
		return (FALSE);
	return (TRUE);
}
static int test_cut33(void)
{
	t_registry *sh;
	t_interface_registry *itf;
	if (create_virtual_registry(&sh, &itf) != 0)
		return (FALSE);

	itf->window->cursor_index = 33;
	ft_strcpy(itf->vector->buffer, "x012345678901234567890123456789xx");

	prepare_clipboard(itf->clipboard, itf->vector);
	move_buffer(itf->clipboard->buffer, itf->vector);

	if (!ft_strequ(itf->clipboard->buffer, "x012345678901234567890123456789xx") || !ft_strequ(itf->vector->buffer, ""))
		return (FALSE);
	return (TRUE);
}
static int test_cut512(void)
{
	t_registry *sh;
	t_interface_registry *itf;
	if (create_virtual_registry(&sh, &itf) != 0)
		return (FALSE);

	itf->window->cursor_index = 0;
	itf->vector = ft_vctnew(512);

	ft_strcpy(itf->vector->buffer, "Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Aenean commodo ligula eget dolor. Aenean massa. Cum sociis natoque penatibus et magnis dis parturient montes, nascetur ridiculus mus. Donec quam felis, ultricies nec, pellentesque eu, pretium quis, sem. Nulla consequat massa quis enim. Donec pede justo, fringilla vel, aliquet nec, vulputate eget, arcu. In enim justo, rhoncus ut, imperdiet a, venenatis vitae, justo. Nullam dictum felis eu pede mollis pretium. Integer tincidunt. Cras dapibus. Vivamus e");

	prepare_clipboard(itf->clipboard, itf->vector);
	move_buffer(itf->clipboard->buffer, itf->vector);

	if (!ft_strequ(itf->clipboard->buffer, "Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Aenean commodo ligula eget dolor. Aenean massa. Cum sociis natoque penatibus et magnis dis parturient montes, nascetur ridiculus mus. Donec quam felis, ultricies nec, pellentesque eu, pretium quis, sem. Nulla consequat massa quis enim. Donec pede justo, fringilla vel, aliquet nec, vulputate eget, arcu. In enim justo, rhoncus ut, imperdiet a, venenatis vitae, justo. Nullam dictum felis eu pede mollis pretium. Integer tincidunt. Cras dapibus. Vivamus e") || !ft_strequ(itf->vector->buffer, ""))
		return (FALSE);
	return (TRUE);
}
 // -------------------------------------------------------------------
static int test_cut_bf(void)
{
	t_registry *sh;
	t_interface_registry *itf;
	if (create_virtual_registry(&sh, &itf) != 0)
		return (FALSE);

	size_t c_pos = 0;
	itf->window->cursor_index = 0;

	prepare_clipboard(itf->clipboard, itf->vector);
	copy_buffer_part(itf->clipboard, itf->vector, itf->window, 1);

	if (c_pos != 0)
		return (FALSE);
	if (!ft_strequ(itf->clipboard->buffer, ""))
		return (FALSE);
	return (TRUE);
}

static int test_cut_bf1(void)
{
	t_registry *sh;
	t_interface_registry *itf;
	if (create_virtual_registry(&sh, &itf) != 0)
		return (FALSE);

	size_t c_pos = 0;
	itf->window->cursor_index = 0;

	ft_strcpy(itf->vector->buffer, "a");

	prepare_clipboard(itf->clipboard, itf->vector);
	copy_buffer_part(itf->clipboard, itf->vector, itf->window, 1);

	c_pos = tc_ak_cut_before_cursor(itf);
	if (c_pos != 0)
		return (FALSE);
	if (!ft_strequ(itf->clipboard->buffer, "") || !ft_strequ(itf->vector->buffer, "a"))
		return (FALSE);
	return (TRUE);
}
static int test_cut_bf32(void)
{
	t_registry *sh;
	t_interface_registry *itf;
	if (create_virtual_registry(&sh, &itf) != 0)
		return (FALSE);

	size_t c_pos = 0;
	itf->window->cursor_index = 32;

	ft_strcpy(itf->vector->buffer, "x012345678901234567890123456789x");

	prepare_clipboard(itf->clipboard, itf->vector);
	copy_buffer_part(itf->clipboard, itf->vector, itf->window, 1);

	if (c_pos != 0)
		return (FALSE);
	if (!ft_strequ(itf->clipboard->buffer, "x012345678901234567890123456789x") || !ft_strequ(itf->vector->buffer, ""))
		return (FALSE);
	return (TRUE);
}
static int test_cut_bf33(void)
{
	t_registry *sh;
	t_interface_registry *itf;
	if (create_virtual_registry(&sh, &itf) != 0)
		return (FALSE);

	size_t c_pos = 0;
	itf->window->cursor_index = 33;

	ft_strcpy(itf->vector->buffer, "x012345678901234567890123456789xx");

	prepare_clipboard(itf->clipboard, itf->vector);
	copy_buffer_part(itf->clipboard, itf->vector, itf->window, 1);

	if (c_pos != 0)
		return (FALSE);
	if (!ft_strequ(itf->clipboard->buffer, "x012345678901234567890123456789xx") || !ft_strequ(itf->vector->buffer, ""))
		return (FALSE);
	return (TRUE);
}
static int test_cut_bf512(void)
{
	t_registry *sh;
	t_interface_registry *itf;
	if (create_virtual_registry(&sh, &itf) != 0)
		return (FALSE);

	size_t c_pos = 0;
	itf->window->cursor_index = 512;

	itf->vector = ft_vctnew(512);
	ft_strcpy(itf->vector->buffer, "Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Aenean commodo ligula eget dolor. Aenean massa. Cum sociis natoque penatibus et magnis dis parturient montes, nascetur ridiculus mus. Donec quam felis, ultricies nec, pellentesque eu, pretium quis, sem. Nulla consequat massa quis enim. Donec pede justo, fringilla vel, aliquet nec, vulputate eget, arcu. In enim justo, rhoncus ut, imperdiet a, venenatis vitae, justo. Nullam dictum felis eu pede mollis pretium. Integer tincidunt. Cras dapibus. Vivamus e");

	prepare_clipboard(itf->clipboard, itf->vector);
	copy_buffer_part(itf->clipboard, itf->vector, itf->window, 1);

	if (c_pos != 0)
		return (FALSE);
	if (!ft_strequ(itf->clipboard->buffer, "Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Aenean commodo ligula eget dolor. Aenean massa. Cum sociis natoque penatibus et magnis dis parturient montes, nascetur ridiculus mus. Donec quam felis, ultricies nec, pellentesque eu, pretium quis, sem. Nulla consequat massa quis enim. Donec pede justo, fringilla vel, aliquet nec, vulputate eget, arcu. In enim justo, rhoncus ut, imperdiet a, venenatis vitae, justo. Nullam dictum felis eu pede mollis pretium. Integer tincidunt. Cras dapibus. Vivamus e") || !ft_strequ(itf->vector->buffer, ""))
		return (FALSE);
	return (TRUE);
}
 // -------------------------------------------------------------------
static int test_cut_af(void)
{
	t_registry *sh;
	t_interface_registry *itf;
	if (create_virtual_registry(&sh, &itf) != 0)
		return (FALSE);

	size_t c_pos = 0;
	itf->window->cursor_index = 0;

	prepare_clipboard(itf->clipboard, itf->vector);
	copy_buffer_part(itf->clipboard, itf->vector, itf->window, 1);

	if (c_pos != 0)
		return (FALSE);
	if (!ft_strequ(itf->clipboard->buffer, ""))
		return (FALSE);
	return (TRUE);
}

static int test_cut_af1(void)
{
	t_registry *sh;
	t_interface_registry *itf;
	if (create_virtual_registry(&sh, &itf) != 0)
		return (FALSE);

	size_t c_pos = 0;
	itf->window->cursor_index = 0;

	ft_strcpy(itf->vector->buffer, "a");

	prepare_clipboard(itf->clipboard, itf->vector);
	copy_buffer_part(itf->clipboard, itf->vector, itf->window, -1);

	if (c_pos != 0)
		return (FALSE);
	if (!ft_strequ(itf->clipboard->buffer, "a") || !ft_strequ(itf->vector->buffer, ""))
		return (FALSE);
	return (TRUE);
}
static int test_cut_af32(void)
{
	t_registry *sh;
	t_interface_registry *itf;
	if (create_virtual_registry(&sh, &itf) != 0)
		return (FALSE);

	size_t c_pos = 0;
	itf->window->cursor_index = 0;

	ft_strcpy(itf->vector->buffer, "x012345678901234567890123456789x");


	prepare_clipboard(itf->clipboard, itf->vector);
	copy_buffer_part(itf->clipboard, itf->vector, itf->window, -1);

	if (c_pos != 0)
		return (FALSE);
	if (!ft_strequ(itf->clipboard->buffer, "x012345678901234567890123456789x") || !ft_strequ(itf->vector->buffer, ""))
		return (FALSE);
	return (TRUE);
}
static int test_cut_af33(void)
{
	t_registry *sh;
	t_interface_registry *itf;
	if (create_virtual_registry(&sh, &itf) != 0)
		return (FALSE);

	itf->window->cursor_index = 33;

	ft_strcpy(itf->vector->buffer, "x012345678901234567890123456789xx");

	prepare_clipboard(itf->clipboard, itf->vector);
	copy_buffer_part(itf->clipboard, itf->vector, itf->window, -1);

	if (itf->window->cursor_index != 33)
		return (FALSE);
	if (!ft_strequ(itf->clipboard->buffer, "") || !ft_strequ(itf->vector->buffer, "x012345678901234567890123456789xx"))
		return (FALSE);
	return (TRUE);
}
static int test_cut_af512(void)
{
	t_registry *sh;
	t_interface_registry *itf;
	if (create_virtual_registry(&sh, &itf) != 0)
		return (FALSE);

	itf->window->cursor_index = 0;

	itf->vector = ft_vctnew(512);
	ft_strcpy(itf->vector->buffer, "Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Aenean commodo ligula eget dolor. Aenean massa. Cum sociis natoque penatibus et magnis dis parturient montes, nascetur ridiculus mus. Donec quam felis, ultricies nec, pellentesque eu, pretium quis, sem. Nulla consequat massa quis enim. Donec pede justo, fringilla vel, aliquet nec, vulputate eget, arcu. In enim justo, rhoncus ut, imperdiet a, venenatis vitae, justo. Nullam dictum felis eu pede mollis pretium. Integer tincidunt. Cras dapibus. Vivamus e");


	prepare_clipboard(itf->clipboard, itf->vector);
	copy_buffer_part(itf->clipboard, itf->vector, itf->window, -1);

	if (!ft_strequ(itf->clipboard->buffer, "Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Aenean commodo ligula eget dolor. Aenean massa. Cum sociis natoque penatibus et magnis dis parturient montes, nascetur ridiculus mus. Donec quam felis, ultricies nec, pellentesque eu, pretium quis, sem. Nulla consequat massa quis enim. Donec pede justo, fringilla vel, aliquet nec, vulputate eget, arcu. In enim justo, rhoncus ut, imperdiet a, venenatis vitae, justo. Nullam dictum felis eu pede mollis pretium. Integer tincidunt. Cras dapibus. Vivamus e") || !ft_strequ(itf->vector->buffer, ""))
		return (FALSE);
	return (TRUE);
}




int		test_clipboard(void)
{
	t_stack tests;

	ft_stckinit(&tests);

	load_test(&tests, "Cut line af :512 bytes |", test_cut_af512);
	load_test(&tests, "Cut line af :33 bytes  |", test_cut_af33);
	load_test(&tests, "Cut line af :32 bytes  |", test_cut_af32);
	load_test(&tests, "Cut line af :1 byte    |", test_cut_af1);
	load_test(&tests, "Cut line af :nothing   |", test_cut_af);

	load_test(&tests, "Cut line bf :512 bytes |", test_cut_bf512);
	load_test(&tests, "Cut line bf :33 bytes  |", test_cut_bf33);
	load_test(&tests, "Cut line bf :32 bytes  |", test_cut_bf32);
	load_test(&tests, "Cut line bf :1 byte    |", test_cut_bf1);
	load_test(&tests, "Cut line bf :nothing   |", test_cut_bf);

	load_test(&tests, "Cut line 512 bytes |", test_cut512);
	load_test(&tests, "Cut line 33 bytes  |", test_cut33);
	load_test(&tests, "Cut line 32 bytes  |", test_cut32);
	load_test(&tests, "Cut line 1 byte    |", test_cut1);
	load_test(&tests, "Cut line nothing   |", test_cut);

	load_test(&tests, "Copy line af: 512 bytes |", test_copy_af512);
	load_test(&tests, "Copy line af: 33 bytes  |", test_copy_af33);
	load_test(&tests, "Copy line af: 32 bytes  |", test_copy_af32);
	load_test(&tests, "Copy line af: 1 byte    |", test_copy_af1);
	load_test(&tests, "Copy line af: nothing   |", test_copy_af);

	load_test(&tests, "Copy line bf: 512 bytes |", test_copy_bf512);
	load_test(&tests, "Copy line bf: 33 bytes  |", test_copy_bf33);
	load_test(&tests, "Copy line bf: 32 bytes  |", test_copy_bf32);
	load_test(&tests, "Copy line bf: 1 byte    |", test_copy_bf1);
	load_test(&tests, "Copy line bf: nothing   |", test_copy_bf);


	load_test(&tests, "Copy line 512 byts", test_copy512);
	load_test(&tests, "Copy line 33 bytes", test_copy33);
	load_test(&tests, "Copy line 32 bytes", test_copy32);
	load_test(&tests, "Copy line 1 byte", test_copy1);
	load_test(&tests, "Copy line nothing", test_copy);


	return (run_test(&tests));
}
