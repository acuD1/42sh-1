/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 14:49:54 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/09 19:10:36 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"
#include "log.h"
#include "ft_printf.h"

static int	allocate_data_structures(t_registry *sh_reg,
		t_vector **vect, t_winsize **ws)
{
	if ((*vect = ft_vctnew(0)) == NULL)
	{
		log_print(sh_reg, LOG_CRITICAL,
				"Error allocating vector memory.\n");
		return (-1);
	}
	if ((*ws = malloc(sizeof(t_winsize))) == NULL)
	{
		log_print(sh_reg, LOG_CRITICAL,
				"Error allocating window memory.\n");
		free(vect);
		return (-1);
	}
	return (0);
}

int	fill_interface_data(t_registry *shell_reg,
		t_interface_registry *itf)
{
	t_vector *vector;
	t_winsize *window;

	if (allocate_data_structures(shell_reg, &vector, &window) != 0)
		return (-1);
	itf->window = window;
	itf->interface_state = INT_PS1_VALUE;
	if ((init_win_struct(shell_reg, itf)) == NULL)
		return (-1);
	itf->line = vector;
	return (0);
}

char		*prompt(t_registry *shell_reg,
				t_interface_registry *itf_reg)
{
	char			ifs_char;
	char			character[READ_SIZE + 1];

	ifs_char = ft_atoi(get_intern_var(shell_reg, INT_IFS));
	if (fill_interface_data(shell_reg, itf_reg) != 0)
		return (NULL);

	ft_bzero(character, READ_SIZE);
	ft_dprintf(STDOUT_FILENO, "\n%s", get_intern_var(shell_reg, INT_PS1));
	while (character[0] != ifs_char)
	{
		ft_bzero(character, READ_SIZE);
		if (read(0, character, READ_SIZE) == -1)
		{
			prompt_read_failed(shell_reg, itf_reg->line);
			return (NULL);
		}
		handle_input_key(character, itf_reg);
		// Ctrl+D EOF handling
		if (itf_reg->line->buffer[0] == 4)
			return (itf_reg->line->buffer);
	}
	tc_ak_end(itf_reg);
	validate_input_quoting(shell_reg, itf_reg);
	// Handle history here
	return (itf_reg->line->buffer);
}
