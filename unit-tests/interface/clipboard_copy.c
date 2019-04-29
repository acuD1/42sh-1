/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clipboard_copy.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 18:10:49 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/15 18:58:00 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "unit.h"
#include "libft.h"

static char global_line[256] = "0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef";

static int test_copyaf_medium(void)
{
	t_registry *sh;
	t_interface *itf;

	if (create_virtual_registry(&sh, &itf) != 0)
		return (FALSE);
// ---------SETUP------------

	size_t BSIZE = 128;
	size_t ICURSOR = 64;

	itf->cursor->index = ICURSOR;
	itf->line->buffer = ft_strnew(BSIZE);
	itf->line->size = BSIZE;
	ft_strncpy(itf->line->buffer, global_line, BSIZE);

// --------TEST--------------

	int8_t res = tc_ak_copy_after_cursor(sh);

// -------RESULT-------------

	//expected :
	char *exp = ft_strsub(global_line, ICURSOR, BSIZE - ICURSOR);

	if (res != 0 || !ft_strequ(exp, itf->clip->buffer))
		return (FALSE);
	return (TRUE);
}

static int test_copybf_medium(void)
{
	t_registry *sh;
	t_interface *itf;

	if (create_virtual_registry(&sh, &itf) != 0)
		return (FALSE);
// ---------SETUP------------

	size_t BSIZE = 128;
	size_t ICURSOR = 64;

	itf->cursor->index = ICURSOR;
	itf->line->buffer = ft_strnew(BSIZE);
	itf->line->size = BSIZE;
	ft_strncpy(itf->line->buffer, global_line, BSIZE);

// --------TEST--------------

	int8_t res = tc_ak_copy_before_cursor(sh);

// -------RESULT-------------

	//expected :
	char *exp = ft_strsub(global_line, 0, ICURSOR);

	if (res != 0 || !ft_strequ(exp, itf->clip->buffer))
		return (FALSE);
	return (TRUE);
}

static int test_copyaf_easy(void)
{
	t_registry *sh;
	t_interface *itf;

	if (create_virtual_registry(&sh, &itf) != 0)
		return (FALSE);
// ---------SETUP------------

	size_t BSIZE = 64;
	size_t ICURSOR = 32;

	itf->cursor->index = ICURSOR;
	itf->line->buffer = ft_strnew(BSIZE);
	itf->line->size = BSIZE;
	ft_strncpy(itf->line->buffer, global_line, BSIZE);

// --------TEST--------------

	int8_t res = tc_ak_copy_after_cursor(sh);

// -------RESULT-------------

	//expected :
	char *exp = ft_strsub(global_line, ICURSOR, BSIZE - ICURSOR);

	if (res != 0 || !ft_strequ(exp, itf->clip->buffer))
		return (FALSE);
	return (TRUE);
}

static int test_copybf_easy(void)
{
	t_registry *sh;
	t_interface *itf;

	if (create_virtual_registry(&sh, &itf) != 0)
		return (FALSE);
// ---------SETUP------------

	size_t BSIZE = 64;
	size_t ICURSOR = 32;

	itf->cursor->index = ICURSOR;
	itf->line->buffer = ft_strnew(BSIZE);
	itf->line->size = BSIZE;
	ft_strncpy(itf->line->buffer, global_line, BSIZE);

// --------TEST--------------

	int8_t res = tc_ak_copy_before_cursor(sh);

// -------RESULT-------------

	//expected :
	char *exp = ft_strsub(global_line, 0, ICURSOR);

	if (res != 0 || !ft_strequ(exp, itf->clip->buffer))
		return (FALSE);
	return (TRUE);
}

static int test_copyall_medium(void)
{
	t_registry *sh;
	t_interface *itf;

	if (create_virtual_registry(&sh, &itf) != 0)
		return (FALSE);
// ---------SETUP------------

	size_t BSIZE = 142;
	itf->line->buffer = ft_strnew(BSIZE);
	itf->line->size = BSIZE;
	ft_strncpy(itf->line->buffer, global_line, BSIZE);

// --------TEST--------------

	int8_t res = tc_ak_copy_line(sh);

// -------RESULT-------------

	if (res != 0 || !ft_strnequ(itf->line->buffer, itf->clip->buffer, BSIZE))
		return (FALSE);
	return (TRUE);
}

static int test_copyall_easy(void)
{
	t_registry *sh;
	t_interface *itf;

	if (create_virtual_registry(&sh, &itf) != 0)
		return (FALSE);

// ---------SETUP------------

	size_t BSIZE = 12;
	itf->line->buffer = ft_strnew(BSIZE);
	itf->line->size = BSIZE;
	ft_strncpy(itf->line->buffer, global_line, BSIZE);

// --------TEST--------------

	int8_t res = tc_ak_copy_line(sh);

// -------RESULT-------------

	if (res != 0 || !ft_strnequ(itf->line->buffer, itf->clip->buffer, BSIZE))
		return (FALSE);
	return (TRUE);
}

static int test_null(void)
{
	t_registry *sh;
	t_interface *itf;

	if (create_virtual_registry(&sh, &itf) != 0)
		return (FALSE);
	sh->interface = NULL;
	int8_t res = tc_ak_copy_line(sh);
	if (res != -1)
		return (FALSE);
	return (TRUE);
}
static int test_null_bf(void)
{
	t_registry *sh;
	t_interface *itf;

	if (create_virtual_registry(&sh, &itf) != 0)
		return (FALSE);
	sh->interface = NULL;
	int8_t res = tc_ak_copy_before_cursor(sh);
	if (res != -1)
		return (FALSE);
	return (TRUE);
}
static int test_null_af(void)
{
	t_registry *sh;
	t_interface *itf;

	if (create_virtual_registry(&sh, &itf) != 0)
		return (FALSE);
	sh->interface = NULL;
	int8_t res = tc_ak_copy_after_cursor(sh);
	if (res != -1)
		return (FALSE);
	return (TRUE);
}

t_result test_clipboard_copy(int print_on)
{
	t_stack tests;

	ft_stckinit(&tests);

	load_test(&tests, "Copy after cursor medium", test_copyaf_medium);
	load_test(&tests, "Copy before cursor medium", test_copybf_medium);
	load_test(&tests, "Copy after cursor easy", test_copyaf_easy);
	load_test(&tests, "Copy before cursor easy", test_copybf_easy);
	load_test(&tests, "Copy line 142chars", test_copyall_medium);
	load_test(&tests, "Copy line 12chars", test_copyall_easy);
	load_test(&tests, "Copy null parameters before", test_null_bf);
	load_test(&tests, "Copy null parameters after", test_null_af);
	load_test(&tests, "Copy null parameters", test_null);

	return (run_test(&tests, "Copy clipboard tests", print_on));
}
