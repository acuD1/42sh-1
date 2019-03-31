/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_shell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 00:22:47 by skuppers          #+#    #+#             */
/*   Updated: 2019/03/31 18:05:00 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "log.h"
#include "line_edit.h"

static void	print_ps2_prompt(t_interface_registry *itf_reg)
{
	itf_reg->window->x = 0;
	itf_reg->window->y = 0;
	ft_printf("\n");
	print_words(PS2_TEXT, itf_reg);
	itf_reg->window->cursor_index = 0;
}

static t_vector *create_ps2_vect(t_interface_registry *itf_reg)
{
	t_vector	*new_vect;
	t_vector	*old_vect;

	new_vect = NULL;
	old_vect = NULL;
	if ((new_vect = ft_vctnew(0)) == NULL)
		return (NULL);
	old_vect = itf_reg->vector;
	itf_reg->vector = new_vect;
	return (old_vect);
}

static int ps2_prompt_loop(t_registry *sh_reg, t_interface_registry *itf_reg,
		t_vector *old_vect)
{
	char		character[READ_SIZE + 1];

	ft_bzero(character, READ_SIZE + 1);
	while (character[0] != IFS_CHARACTER)
	{
		ft_bzero(character, READ_SIZE);
		if (read(0, character, READ_SIZE) == -1)
		{
			prompt_read_failed(sh_reg, itf_reg->vector);
			return (-2);
		}
		itf_reg->window->cursor_index = handle_input_key(character, itf_reg);
		if (itf_reg->vector->buffer[0] == 4)
		{
			ft_strdel(&(itf_reg->vector->buffer));
			free(itf_reg->vector);
			itf_reg->vector = old_vect;
			return (-4);
		}
	}
	return (0);
}

int		invoke_ps2_prompt(t_registry *sh_reg, t_interface_registry *itf_reg)
{
	char		*concat;
	t_vector	*old_vect;

	concat = NULL;
	old_vect = NULL;
	if ((old_vect = create_ps2_vect(itf_reg)) == NULL)
		return (-1);
	print_ps2_prompt(itf_reg);
	if (ps2_prompt_loop(sh_reg, itf_reg, old_vect) != 0)
		return (-1);
	ft_asprintf(&concat, "%s%s", old_vect->buffer, itf_reg->vector->buffer);
	ft_strdel(&(old_vect->buffer));
	free(old_vect);
	ft_strdel(&(itf_reg->vector->buffer));
	itf_reg->vector->buffer = concat;
	itf_reg->vector->size = ft_strlen(concat);
	return (0);
}
