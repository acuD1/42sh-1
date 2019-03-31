/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 14:49:54 by skuppers          #+#    #+#             */
/*   Updated: 2019/03/31 16:41:22 by skuppers         ###   ########.fr       */
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

static int	fill_interface_data(t_registry *shell_reg,
		t_interface_registry *itf, t_vector *vector, t_winsize *window)
{
	if (allocate_data_structures(shell_reg, &vector, &window) != 0)
		return (-1);
	if ((init_win_struct(shell_reg, window)) == NULL)
		return (-1);
	itf->window = window;
	itf->vector = vector;
	itf->interface_state = PS1;
	return (0);
}

char	*prompt(t_registry *shell_reg, t_interface_registry *itf_reg)
{
	char			character[READ_SIZE + 1];
	t_vector		*vector;
	t_winsize		*window;

	vector = NULL;
	window = NULL;
	if (fill_interface_data(shell_reg, itf_reg, vector, window) != 0)
		return (NULL);
	ft_bzero(character, READ_SIZE);
	ft_dprintf(STDOUT_FILENO, "\n%s", PROMPT_TEXT);
	while (character[0] != IFS_CHARACTER)
	{
		ft_bzero(character, READ_SIZE);
		if (read(0, character, READ_SIZE) == -1)
		{
			prompt_read_failed(shell_reg, vector);
			return (NULL);
		}
		itf_reg->window->cursor_index = handle_input_key(character, itf_reg);
		/* Ctrl+D EOF handling*/
		if (itf_reg->vector->buffer[0] == 4)
			return (itf_reg->vector->buffer);
	}
	itf_reg->window->cursor_index = tc_ak_end(itf_reg);
	validate_input_quoting(shell_reg, itf_reg);
	// Handle history here
	return (itf_reg->vector->buffer);
}
