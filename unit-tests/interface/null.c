/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   null.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 11:45:17 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/10 15:51:40 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unit.h"

static int test0_cl(void)
{
	int c_pos = 0;

	c_pos = tc_ak_cut_line(NULL);
	if (c_pos != -1)
		return (FALSE);
	return (TRUE);
}
static int test1_cl(void)
{
	t_registry *sh;
	t_interface_registry *itf;
	if (create_virtual_registry(&sh, &itf) != 0)
		return (FALSE);

	itf->clip = NULL;

	int c_pos = 0;
	itf->window->cursor = 0;
	c_pos = tc_ak_cut_line(itf);
	if (c_pos != -1)
		return (FALSE);
	return (TRUE);
}
static int test2_cl(void)
{
	t_registry *sh;
	t_interface_registry *itf;
	if (create_virtual_registry(&sh, &itf) != 0)
		return (FALSE);

	itf->line = NULL;

	int c_pos = 0;
	itf->window->cursor = 0;
	c_pos = tc_ak_cut_line(itf);
	if (c_pos != -1)
		return (FALSE);
	return (TRUE);
}
static int test3_cl(void)
{
	t_registry *sh;
	t_interface_registry *itf;
	if (create_virtual_registry(&sh, &itf) != 0)
		return (FALSE);

	itf->clip->buffer = NULL;

	int c_pos = 0;
	itf->window->cursor = 0;
	c_pos = tc_ak_cut_line(itf);
	if (c_pos != -1)
		return (FALSE);
	return (TRUE);
}
static int test4_cl(void)
{
	t_registry *sh;
	t_interface_registry *itf;
	if (create_virtual_registry(&sh, &itf) != 0)
		return (FALSE);

	itf->line->buffer = NULL;

	int c_pos = 0;
	itf->window->cursor = 0;
	c_pos = tc_ak_cut_line(itf);
	if (c_pos != -1)
		return (FALSE);
	return (TRUE);
}

//---------------------------------------------------------

static int test0_cl_bf(void)
{
	int c_pos = 0;

	c_pos = tc_ak_cut_before_cursor(NULL);
	if (c_pos != -1)
		return (FALSE);
	return (TRUE);
}
static int test1_cl_bf(void)
{
	t_registry *sh;
	t_interface_registry *itf;
	if (create_virtual_registry(&sh, &itf) != 0)
		return (FALSE);

	itf->clip = NULL;

	int c_pos = 0;
	itf->window->cursor = 0;
	c_pos = tc_ak_cut_before_cursor(itf);
	if (c_pos != -1)
		return (FALSE);
	return (TRUE);
}
static int test2_cl_bf(void)
{
	t_registry *sh;
	t_interface_registry *itf;
	if (create_virtual_registry(&sh, &itf) != 0)
		return (FALSE);

	itf->line = NULL;

	int c_pos = 0;
	itf->window->cursor = 0;
	c_pos = tc_ak_cut_before_cursor(itf);
	if (c_pos != -1)
		return (FALSE);
	return (TRUE);
}
static int test3_cl_bf(void)
{
	t_registry *sh;
	t_interface_registry *itf;
	if (create_virtual_registry(&sh, &itf) != 0)
		return (FALSE);

	itf->clip->buffer = NULL;

	int c_pos = 0;
	itf->window->cursor = 0;
	c_pos = tc_ak_cut_before_cursor(itf);
	if (c_pos != -1)
		return (FALSE);
	return (TRUE);
}
static int test4_cl_bf(void)
{
	t_registry *sh;
	t_interface_registry *itf;
	if (create_virtual_registry(&sh, &itf) != 0)
		return (FALSE);

	itf->line->buffer = NULL;

	int c_pos = 0;
	itf->window->cursor = 0;
	c_pos = tc_ak_cut_before_cursor(itf);
	if (c_pos != -1)
		return (FALSE);
	return (TRUE);
}

// -----------------------------------------------------

static int test0_cl_af(void)
{
	int c_pos = 0;

	c_pos = tc_ak_cut_after_cursor(NULL);
	if (c_pos != -1)
		return (FALSE);
	return (TRUE);
}
static int test1_cl_af(void)
{
	t_registry *sh;
	t_interface_registry *itf;
	if (create_virtual_registry(&sh, &itf) != 0)
		return (FALSE);

	itf->clip = NULL;

	int c_pos = 0;
	itf->window->cursor = 0;
	c_pos = tc_ak_cut_after_cursor(itf);
	if (c_pos != -1)
		return (FALSE);
	return (TRUE);
}
static int test2_cl_af(void)
{
	t_registry *sh;
	t_interface_registry *itf;
	if (create_virtual_registry(&sh, &itf) != 0)
		return (FALSE);

	itf->line = NULL;

	int c_pos = 0;
	itf->window->cursor = 0;
	c_pos = tc_ak_cut_after_cursor(itf);
	if (c_pos != -1)
		return (FALSE);
	return (TRUE);
}
static int test3_cl_af(void)
{
	t_registry *sh;
	t_interface_registry *itf;
	if (create_virtual_registry(&sh, &itf) != 0)
		return (FALSE);

	itf->clip->buffer = NULL;

	int c_pos = 0;
	itf->window->cursor = 0;
	c_pos = tc_ak_cut_after_cursor(itf);
	if (c_pos != -1)
		return (FALSE);
	return (TRUE);
}
static int test4_cl_af(void)
{
	t_registry *sh;
	t_interface_registry *itf;
	if (create_virtual_registry(&sh, &itf) != 0)
		return (FALSE);

	itf->line->buffer = NULL;

	int c_pos = 0;
	itf->window->cursor = 0;
	c_pos = tc_ak_cut_after_cursor(itf);
	if (c_pos != -1)
		return (FALSE);
	return (TRUE);
}

// -----------------------------------------------------

static int test0_cp(void)
{
	int c_pos = 0;

	c_pos = tc_ak_copy_line(NULL);
	if (c_pos != -1)
		return (FALSE);
	return (TRUE);
}
static int test1_cp(void)
{
	t_registry *sh;
	t_interface_registry *itf;
	if (create_virtual_registry(&sh, &itf) != 0)
		return (FALSE);

	itf->clip = NULL;

	int c_pos = 0;
	itf->window->cursor = 0;
	c_pos = tc_ak_copy_line(itf);
	if (c_pos != -1)
		return (FALSE);
	return (TRUE);
}
static int test2_cp(void)
{
	t_registry *sh;
	t_interface_registry *itf;
	if (create_virtual_registry(&sh, &itf) != 0)
		return (FALSE);

	itf->line = NULL;

	int c_pos = 0;
	itf->window->cursor = 0;
	c_pos = tc_ak_copy_line(itf);
	if (c_pos != -1)
		return (FALSE);
	return (TRUE);
}
static int test3_cp(void)
{
	t_registry *sh;
	t_interface_registry *itf;
	if (create_virtual_registry(&sh, &itf) != 0)
		return (FALSE);

	itf->clip->buffer = NULL;

	int c_pos = 0;
	itf->window->cursor = 0;
	c_pos = tc_ak_copy_line(itf);
	if (c_pos != -1)
		return (FALSE);
	return (TRUE);
}
static int test4_cp(void)
{
	t_registry *sh;
	t_interface_registry *itf;
	if (create_virtual_registry(&sh, &itf) != 0)
		return (FALSE);

	itf->line->buffer = NULL;

	int c_pos = 0;
	itf->window->cursor = 0;
	c_pos = tc_ak_copy_line(itf);
	if (c_pos != -1)
		return (FALSE);
	return (TRUE);
}

//---------------------------------------------------------

static int test0_cp_bf(void)
{
	int c_pos = 0;

	c_pos = tc_ak_copy_before_cursor(NULL);
	if (c_pos != -1)
		return (FALSE);
	return (TRUE);
}
static int test1_cp_bf(void)
{
	t_registry *sh;
	t_interface_registry *itf;
	if (create_virtual_registry(&sh, &itf) != 0)
		return (FALSE);

	itf->clip = NULL;

	int c_pos = 0;
	itf->window->cursor = 0;
	c_pos = tc_ak_copy_before_cursor(itf);
	if (c_pos != -1)
		return (FALSE);
	return (TRUE);
}
static int test2_cp_bf(void)
{
	t_registry *sh;
	t_interface_registry *itf;
	if (create_virtual_registry(&sh, &itf) != 0)
		return (FALSE);

	itf->line = NULL;

	int c_pos = 0;
	itf->window->cursor = 0;
	c_pos = tc_ak_copy_before_cursor(itf);
	if (c_pos != -1)
		return (FALSE);
	return (TRUE);
}
static int test3_cp_bf(void)
{
	t_registry *sh;
	t_interface_registry *itf;
	if (create_virtual_registry(&sh, &itf) != 0)
		return (FALSE);

	itf->clip->buffer = NULL;

	int c_pos = 0;
	itf->window->cursor = 0;
	c_pos = tc_ak_copy_before_cursor(itf);
	if (c_pos != -1)
		return (FALSE);
	return (TRUE);
}
static int test4_cp_bf(void)
{
	t_registry *sh;
	t_interface_registry *itf;
	if (create_virtual_registry(&sh, &itf) != 0)
		return (FALSE);

	itf->line->buffer = NULL;

	int c_pos = 0;
	itf->window->cursor = 0;
	c_pos = tc_ak_copy_before_cursor(itf);
	if (c_pos != -1)
		return (FALSE);
	return (TRUE);
}

// -----------------------------------------------------

static int test0_cp_af(void)
{
	int c_pos = 0;

	c_pos = tc_ak_copy_after_cursor(NULL);
	if (c_pos != -1)
		return (FALSE);
	return (TRUE);
}
static int test1_cp_af(void)
{
	t_registry *sh;
	t_interface_registry *itf;
	if (create_virtual_registry(&sh, &itf) != 0)
		return (FALSE);

	itf->clip = NULL;

	int c_pos = 0;
	itf->window->cursor = 0;
	c_pos = tc_ak_copy_after_cursor(itf);
	if (c_pos != -1)
		return (FALSE);
	return (TRUE);
}
static int test2_cp_af(void)
{
	t_registry *sh;
	t_interface_registry *itf;
	if (create_virtual_registry(&sh, &itf) != 0)
		return (FALSE);

	itf->line = NULL;

	int c_pos = 0;
	itf->window->cursor = 0;
	c_pos = tc_ak_copy_after_cursor(itf);
	if (c_pos != -1)
		return (FALSE);
	return (TRUE);
}
static int test3_cp_af(void)
{
	t_registry *sh;
	t_interface_registry *itf;
	if (create_virtual_registry(&sh, &itf) != 0)
		return (FALSE);

	itf->clip->buffer = NULL;

	int c_pos = 0;
	itf->window->cursor = 0;
	c_pos = tc_ak_copy_after_cursor(itf);
	if (c_pos != -1)
		return (FALSE);
	return (TRUE);
}
static int test4_cp_af(void)
{
	t_registry *sh;
	t_interface_registry *itf;
	if (create_virtual_registry(&sh, &itf) != 0)
		return (FALSE);

	itf->line->buffer = NULL;

	int c_pos = 0;
	itf->window->cursor = 0;
	c_pos = tc_ak_copy_after_cursor(itf);
	if (c_pos != -1)
		return (FALSE);
	return (TRUE);
}
// --------------------------------------------------------------
static int test_paste1(void)
{
	int c_pos = 0;
	c_pos = tc_ak_paste_clipboard(NULL);
	if (c_pos != -1)
		return (FALSE);
	return (TRUE);
}
static int test_paste2(void)
{
	t_registry *sh;
	t_interface_registry *itf;
	if (create_virtual_registry(&sh, &itf) != 0)
		return (FALSE);

	itf->clip = NULL;

	int c_pos = 0;
	itf->window->cursor = 0;
	c_pos = tc_ak_paste_clipboard(itf);
	if (c_pos != -1)
		return (FALSE);
	return (TRUE);
}
static int test_paste3(void)
{
	t_registry *sh;
	t_interface_registry *itf;
	if (create_virtual_registry(&sh, &itf) != 0)
		return (FALSE);

	itf->line = NULL;

	int c_pos = 0;
	itf->window->cursor = 0;
	c_pos = tc_ak_paste_clipboard(itf);
	if (c_pos != -1)
		return (FALSE);
	return (TRUE);
}
static int test_paste4(void)
{
	t_registry *sh;
	t_interface_registry *itf;
	if (create_virtual_registry(&sh, &itf) != 0)
		return (FALSE);

	itf->clip->buffer = NULL;

	int c_pos = 0;
	itf->window->cursor = 0;
	c_pos = tc_ak_paste_clipboard(itf);
	if (c_pos != -1)
		return (FALSE);
	return (TRUE);
}
static int test_paste5(void)
{
	t_registry *sh;
	t_interface_registry *itf;
	if (create_virtual_registry(&sh, &itf) != 0)
		return (FALSE);

	itf->line->buffer = NULL;

	int c_pos = 0;
	itf->window->cursor = 0;
	c_pos = tc_ak_paste_clipboard(itf);
	if (c_pos != -1)
		return (FALSE);
	return (TRUE);
}



t_result test_null_value(void)
{
	t_stack tests;

	ft_stckinit(&tests);

	load_test(&tests, "paste | NULL param     |", test_paste1);
	load_test(&tests, "paste | NULL clipboard |", test_paste2);
	load_test(&tests, "paste | NULL vector    |", test_paste3);
	load_test(&tests, "paste | NULL c buffer  |", test_paste4);
	load_test(&tests, "paste | NULL v buffer  |", test_paste5);

	load_test(&tests, "copy after | NULL param     |", test0_cp_af);
	load_test(&tests, "copy after | NULL clipboard |", test1_cp_af);
	load_test(&tests, "copy after | NULL vector    |", test2_cp_af);
	load_test(&tests, "copy after | NULL c buffer  |", test3_cp_af);
	load_test(&tests, "copy after | NULL v buffer  |", test4_cp_af);

	load_test(&tests, "copy before | NULL param     |", test0_cp_bf);
	load_test(&tests, "copy before | NULL clipboard |", test1_cp_bf);
	load_test(&tests, "copy before | NULL vector    |", test2_cp_bf);
	load_test(&tests, "copy before | NULL c buffer  |", test3_cp_bf);
	load_test(&tests, "copy before | NULL v buffer  |", test4_cp_bf);

	load_test(&tests, "copy line | NULL param     |", test0_cp);
	load_test(&tests, "copy line | NULL clipboard |", test1_cp);
	load_test(&tests, "copy line | NULL vector    |", test2_cp);
	load_test(&tests, "copy line | NULL c buffer  |", test3_cp);
	load_test(&tests, "copy line | NULL v buffer  |", test4_cp);

	load_test(&tests, "cut after | NULL param     |", test0_cl_af);
	load_test(&tests, "cut after | NULL clipboard |", test1_cl_af);
	load_test(&tests, "cut after | NULL vector    |", test2_cl_af);
	load_test(&tests, "cut after | NULL c buffer  |", test3_cl_af);
	load_test(&tests, "cut after | NULL v buffer  |", test4_cl_af);

	load_test(&tests, "cut before | NULL param     |", test0_cl_bf);
	load_test(&tests, "cut before | NULL clipboard |", test1_cl_bf);
	load_test(&tests, "cut before | NULL vector    |", test2_cl_bf);
	load_test(&tests, "cut before | NULL c buffer  |", test3_cl_bf);
	load_test(&tests, "cut before | NULL v buffer  |", test4_cl_bf);

	load_test(&tests, "cut line | NULL param     |", test0_cl);
	load_test(&tests, "cut line | NULL clipboard |", test1_cl);
	load_test(&tests, "cut line | NULL vector    |", test2_cl);
	load_test(&tests, "cut line | NULL c buffer  |", test3_cl);
	load_test(&tests, "cut line | NULL v buffer  |", test4_cl);
	ft_printf("Clipboard null value protection : \n");
	return (run_test(&tests, "NULL Protection"));
}
