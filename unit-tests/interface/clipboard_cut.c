/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clipboard_cut.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 18:47:51 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/15 19:18:19 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unit.h"
#include "libft.h"

static char global_line[256] = "0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef";

static int test_cutaf_medium(void)
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

	realloc_vector(itf->clip, itf->line);
	copy_buffer_part(itf, -1);

// -------RESULT-------------

	//expected :
	char *exp = ft_strsub(global_line, ICURSOR, BSIZE - ICURSOR);
	char *exp_line = ft_strsub(global_line, 0, ICURSOR);

	if (!ft_strequ(exp_line, itf->line->buffer)
		|| !ft_strequ(exp, itf->clip->buffer))
		return (FALSE);
	return (TRUE);
}

static int test_cutbf_medium(void)
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

	realloc_vector(itf->clip, itf->line);
	copy_buffer_part(itf, 1);

// -------RESULT-------------

	//expected :
	char *exp = ft_strsub(global_line, 0, ICURSOR);
	char *exp_line = ft_strsub(global_line, ICURSOR, BSIZE - ICURSOR);

	if (!ft_strequ(exp, itf->clip->buffer)
		|| !ft_strequ(exp_line, itf->line->buffer))
		return (FALSE);
	return (TRUE);
}

static int test_cutaf_easy(void)
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

	realloc_vector(itf->clip, itf->line);
	copy_buffer_part(itf, -1);

// -------RESULT-------------

	//expected :
	char *exp = ft_strsub(global_line, ICURSOR, BSIZE - ICURSOR);
	char *exp_line = ft_strsub(global_line, 0, ICURSOR);

	if (!ft_strequ(exp, itf->clip->buffer)
	|| !ft_strequ(exp_line, itf->line->buffer))
		return (FALSE);
	return (TRUE);
}

static int test_cutbf_easy(void)
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

	realloc_vector(itf->clip, itf->line);
	copy_buffer_part(itf, 1);

// -------RESULT-------------

	//expected :
	char *exp = ft_strsub(global_line, 0, ICURSOR);
	char *exp_line = ft_strsub(global_line, ICURSOR, BSIZE - ICURSOR);

	if (!ft_strequ(exp, itf->clip->buffer)
	|| !ft_strequ(exp_line, itf->line->buffer))
		return (FALSE);
	return (TRUE);
}

static int test_cutall_medium(void)
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

	realloc_vector(itf->clip, itf->line);
	move_buffer(itf->clip->buffer, itf->line);

// -------RESULT-------------
	//expected :
	char *exp = ft_strsub(global_line, 0, BSIZE);

	if (!ft_strequ(exp, itf->clip->buffer) || ft_strlen(itf->line->buffer) != 0)
		return (FALSE);
	return (TRUE);
}

static int test_cutall_easy(void)
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

	realloc_vector(itf->clip, itf->line);
	move_buffer(itf->clip->buffer, itf->line);

// -------RESULT-------------

	//expected :
	char *exp = ft_strsub(global_line, 0, BSIZE);

	if (!ft_strequ(exp, itf->clip->buffer))
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
	int8_t res = tc_ak_cut_line(sh);
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
	int8_t res = tc_ak_cut_before_cursor(sh);
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
	int8_t res = tc_ak_cut_after_cursor(sh);
	if (res != -1)
		return (FALSE);
	return (TRUE);
}

t_result test_clipboard_cut(int print_on)
{
	t_stack tests;

	ft_stckinit(&tests);

	load_test(&tests, "Cut after cursor medium", test_cutaf_medium);
	load_test(&tests, "Cut before cursor medium", test_cutbf_medium);
	load_test(&tests, "Cut after cursor easy", test_cutaf_easy);
	load_test(&tests, "Cut before cursor easy", test_cutbf_easy);
	load_test(&tests, "Cut line 142chars", test_cutall_medium);
	load_test(&tests, "Cut line 12chars", test_cutall_easy);

	load_test(&tests, "Cut null parameters before", test_null_bf);
	load_test(&tests, "Cut null parameters after", test_null_af);
	load_test(&tests, "Cut null parameters", test_null);

	return (run_test(&tests, "Cut clipboard tests", print_on));
}
