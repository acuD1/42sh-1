/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_shell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 00:22:47 by skuppers          #+#    #+#             */
/*   Updated: 2019/03/28 18:43:11 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#include "line_edit.h"
#include "log.h"
#include "libft.h"

int		invoke_ps2_prompt(t_registry *sh_reg, t_interface_registry *itf_reg)
{
	char		*concat;
	t_vector	*new_vect;
	t_vector	*old_vect;
	char	character[READ_SIZE + 1];

	concat = NULL;
	new_vect = NULL;
	old_vect = NULL;
	ft_bzero(character, READ_SIZE + 1);
	if ((new_vect = ft_vctnew(0)) == NULL)
		return (-1);

	old_vect = itf_reg->vector;
	itf_reg->vector = new_vect;

	itf_reg->window->x = 0;
	itf_reg->window->y = 0;
	ft_printf("\n");
	print_words(PS2_TEXT, itf_reg);
	itf_reg->window->cursor_index = 0;

	while (character[0] != IFS_CHARACTER)
	{
		ft_bzero(character, READ_SIZE);
		if (read(0, character, READ_SIZE) == -1)
		{
			prompt_read_failed(sh_reg, new_vect);
			return (-2);
		}
		itf_reg->window->cursor_index = handle_input_key(character, itf_reg);

		if (new_vect->buffer[0] == 4)
		{
			ft_strdel(&(new_vect->buffer));
			free(new_vect);
			itf_reg->vector = old_vect;
			return (-4);
		}
	}
	ft_asprintf(&concat, "%s%s", old_vect->buffer, new_vect->buffer);
	ft_strdel(&(old_vect->buffer));
	free(old_vect);
	ft_strdel(&(itf_reg->vector->buffer));
	itf_reg->vector->buffer = concat;
	itf_reg->vector->size = ft_strlen(concat);
	return (0);
}
