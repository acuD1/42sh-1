/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_virt_registry.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 11:42:13 by skuppers          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2019/04/11 17:25:44 by cempassi         ###   ########.fr       */
=======
/*   Updated: 2019/04/15 13:04:37 by skuppers         ###   ########.fr       */
>>>>>>> interface
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
	(*itf)->window->max_chars = 65535;
	(*itf)->cursor->index = 0;
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

<<<<<<< HEAD
t_result test_virt_registry(int print_on)
=======
t_result test_virt_registry(void)
>>>>>>> interface
{
	t_stack tests;

	ft_stckinit(&tests);

	load_test(&tests, "Virtual registry creation", test_creation);

<<<<<<< HEAD
	return (run_test(&tests, "Virtual registry", print_on));
=======
	return (run_test(&tests, "Registry creation"));
>>>>>>> interface
}
