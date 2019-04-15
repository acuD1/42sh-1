/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clipboard_paste.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 19:10:13 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/15 19:27:23 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unit.h"
#include "libft.h"

static char global_line[256] = "0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef";

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

//	load_test(&tests, "Cut null parameters before", test_null_bf);
	load_test(&tests, "Paste easy", test_paste_easy);
	load_test(&tests, "Paste null parameters", test_null);

	return (run_test(&tests, "Cut clipboard tests", print_on));
}
