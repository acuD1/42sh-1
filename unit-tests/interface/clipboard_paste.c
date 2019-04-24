/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clipboard_paste.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 19:10:13 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/16 10:46:45 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unit.h"
#include "libft.h"

static char global_line[256] = "0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef";

static int test_paste_insert_m(void)
{
	t_registry *sh;
	t_interface *itf;

	if (create_virtual_registry(&sh, &itf) != 0)
		return (FALSE);
// ---------SETUP------------

	size_t BSIZE = 128;
	itf->line->buffer = ft_strnew(BSIZE);
	itf->line->size = BSIZE;
	ft_strncpy(itf->line->buffer, global_line, BSIZE);

	itf->clip->buffer = ft_strnew(BSIZE);
	itf->clip->size = BSIZE;
	ft_strncpy(itf->clip->buffer, global_line, BSIZE / 2);

	itf->cursor->index = 84;

// --------TEST--------------

	if (is_too_long(itf->line, itf->clip, itf->window->max_chars))
		return (TRUE);
	while (itf->line->size < (ft_vctlen(itf->line) + ft_vctlen(itf->clip) + 2))
		ft_vctrescale(itf->line);
	insert_clipboard(sh);

// -------RESULT-------------

	char *exp = NULL;
	ft_asprintf(&exp, "%s%s%s",ft_strsub(global_line, 0, 84), itf->clip->buffer,
					ft_strsub(global_line, 84, BSIZE - 84));

	if (!ft_strequ(itf->line->buffer, exp))
		return (FALSE);
	return (TRUE);
}

static int test_paste_insert_e(void)
{
	t_registry *sh;
	t_interface *itf;

	if (create_virtual_registry(&sh, &itf) != 0)
		return (FALSE);
// ---------SETUP------------

	size_t BSIZE = 32;
	itf->line->buffer = ft_strnew(BSIZE);
	itf->line->size = BSIZE;
	ft_strncpy(itf->line->buffer, global_line, BSIZE);

	itf->clip->buffer = ft_strnew(BSIZE);
	itf->clip->size = BSIZE;
	ft_strncpy(itf->clip->buffer, global_line, BSIZE);

	itf->cursor->index = 16;

// --------TEST--------------

	if (is_too_long(itf->line, itf->clip, itf->window->max_chars))
		return (TRUE);
	while (itf->line->size < (ft_vctlen(itf->line) + ft_vctlen(itf->clip) + 2))
		ft_vctrescale(itf->line);
	insert_clipboard(sh);

// -------RESULT-------------

	char *exp = NULL;
	ft_asprintf(&exp, "%s%s%s",ft_strsub(global_line, 0, 16), itf->clip->buffer,
					ft_strsub(global_line, 16, 16));

	if (!ft_strequ(itf->line->buffer, exp))
		return (FALSE);
	return (TRUE);
}

static int test_paste_medium(void)
{
	t_registry *sh;
	t_interface *itf;

	if (create_virtual_registry(&sh, &itf) != 0)
		return (FALSE);
// ---------SETUP------------

	size_t BSIZE = 242;
	itf->clip->buffer = ft_strnew(BSIZE);
	itf->clip->size = BSIZE;
	ft_strncpy(itf->clip->buffer, global_line, BSIZE-1);


// --------TEST--------------

	if (is_too_long(itf->line, itf->clip, itf->window->max_chars))
		return (TRUE);
	while (itf->line->size < (ft_vctlen(itf->line) + ft_vctlen(itf->clip) + 2))
		ft_vctrescale(itf->line);
	itf->line->buffer = ft_strcat(itf->line->buffer, itf->clip->buffer);

// -------RESULT-------------

	if (!ft_strequ(itf->line->buffer, itf->clip->buffer))
		return (FALSE);
	return (TRUE);
}

static int test_paste_easy(void)
{
	t_registry *sh;
	t_interface *itf;

	if (create_virtual_registry(&sh, &itf) != 0)
		return (FALSE);
// ---------SETUP------------

	size_t BSIZE = 64;
	itf->clip->buffer = ft_strnew(BSIZE);
	itf->clip->size = BSIZE;
	ft_strncpy(itf->clip->buffer, global_line, BSIZE-1);


// --------TEST--------------

	if (is_too_long(itf->line, itf->clip, itf->window->max_chars))
		return (TRUE);
	while (itf->line->size < (ft_vctlen(itf->line) + ft_vctlen(itf->clip) + 2))
		ft_vctrescale(itf->line);
	itf->line->buffer = ft_strcat(itf->line->buffer, itf->clip->buffer);

// -------RESULT-------------

	if (!ft_strequ(itf->line->buffer, itf->clip->buffer))
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

	int8_t res = tc_ak_paste_clipboard(sh);
	if (res != -1)
		return (FALSE);
	return (TRUE);
}

t_result test_clipboard_paste(int print_on)
{
	t_stack tests;

	ft_stckinit(&tests);

	load_test(&tests, "Paste insert medium", test_paste_insert_m);
	load_test(&tests, "Paste insert easy", test_paste_insert_e);
	load_test(&tests, "Paste medium", test_paste_medium);
	load_test(&tests, "Paste easy", test_paste_easy);
	load_test(&tests, "Paste null parameters", test_null);

	return (run_test(&tests, "Cut clipboard tests", print_on));
}
