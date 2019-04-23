/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_shell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 00:22:47 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/23 19:32:30 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "log.h"
#include "line_edit.h"
#include "interface_functions.h"

static void			print_sub_prompt(t_registry *shell)
{
	shell->interface->cursor->x = 0;
	shell->interface->cursor->y = 0;
	ft_printf("\n");
	print_words(get_intern_var(shell, shell->interface->state),
					shell->interface);
	shell->interface->cursor->index = 0;
}
/*
static t_vector		*copy_vector(t_vector *src)
{
	t_vector	*old_vect;

	old_vect = NULL;
	if ((old_vect = ft_vctnew(src->size + 1)) == NULL)
		return (NULL);
	ft_strncpy(old_vect->buffer, src->buffer, src->size);
	return (old_vect);
}
*/
static int8_t		sub_prompt_loop(t_registry *shell, t_interface *itf)
{
	char		character[READ_SIZE + 1];

	ft_bzero(character, READ_SIZE + 1);
	while (character[0] != IFS_CHAR)
	{
		ft_bzero(character, READ_SIZE);
		if (read(0, character, READ_SIZE) == -1)
		{
			prompt_read_failed(shell, itf->line);
			return (-2);
		}
		handle_input_key(character, shell);
		if (is_eof(itf->line->buffer))
		{
			ft_strdel(&(itf->line->buffer));
			free(itf->line);
			itf->line = ft_vctnew(0);
			return (-4);
		}
	}
	return (0);
}

int8_t				invoke_sub_prompt(t_registry *shell, char **line,
				char *prompt_state)
{
	t_interface		*itf;

	itf = shell->interface;
	itf->state = prompt_state;

	if (validate_interface_content(itf) != 0)
		return (-1);

	reset_vector(itf->line);
	print_sub_prompt(shell);
	if (sub_prompt_loop(shell, itf) != 0)
	{
		reset_vector(itf->line);
		return (-3);
	}
	*line = ft_strdup(itf->line->buffer);
	ft_strdel(&(itf->line->buffer));
	itf->line->buffer = NULL;
	return (0);
}
