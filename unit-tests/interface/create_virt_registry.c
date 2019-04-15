/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_virt_registry.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 11:42:13 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/15 18:47:35 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unit.h"
#include "libft.h"

int create_virtual_registry(t_registry **sh, t_interface **itf)
{
	t_opt *options;

	*sh = malloc(sizeof(t_registry));
	ft_memset(*sh, 0, sizeof(t_registry));

	options = malloc(sizeof(t_opt));
	ft_memset(options, 0, sizeof(t_opt));

	if (*sh == NULL || options == NULL)
			return (-1);

	options->d = 0;
	(*sh)->option = *options;
	*itf = init_line_edition(*sh);
	if (itf == NULL)
			return (-1);

	if (fill_interface_data(*sh, *itf) != 0)
		return (-1);
	(*itf)->window->max_chars = 256;
	return (0);
}

static int test_creation(void)
{
	t_registry *sh;
	t_interface *itf;

	if (create_virtual_registry(&sh, &itf) != 0)
		return (FALSE);
	return (TRUE);
}

t_result test_virt_registry(int print_on)
{
	t_stack tests;

	ft_stckinit(&tests);

	load_test(&tests, "Virtual registry creation", test_creation);

	return (run_test(&tests, "Virtual registry", print_on));
}
