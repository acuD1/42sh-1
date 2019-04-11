/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_shell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 00:22:47 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/11 18:17:07 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "log.h"
#include "line_edit.h"

static void		print_ps2_prompt(t_interface *itf)
{
	itf->cursor->x = 0;
	itf->cursor->y = 0;
	ft_printf("\n");
	print_words(get_intern_var(itf->shell, INT_PS2), itf);
	itf->cursor->index = 0;
}

static t_vector	*create_ps2_vect(t_interface *itf)
{
	t_vector	*new_vect;
	t_vector	*old_vect;

	new_vect = NULL;
	old_vect = NULL;
	if ((new_vect = ft_vctnew(0)) == NULL)
		return (NULL);
	old_vect = itf->line;
	itf->line = new_vect;
	return (old_vect);
}

static int8_t	ps2_prompt_loop(t_registry *shell, t_interface *itf, t_vector *old_vect)
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
		handle_input_key(character, itf);
		if (is_EOF(itf->line->buffer))
		{
			ft_strdel(&(itf->line->buffer));
			free(itf->line);
			ft_strdel(&(old_vect->buffer));
			free(old_vect);
			itf->line = ft_vctnew(0);
			return (-4);
		}
	}
	return (0);
}

int8_t			invoke_ps2_prompt(t_registry *shell, t_interface *itf)
{
	char		*concat;
	t_vector	*old_vect;

	concat = NULL;
	old_vect = NULL;

	if ((old_vect = create_ps2_vect(itf)) == NULL)
		return (-1);

	print_ps2_prompt(itf);

	if (ps2_prompt_loop(shell, itf, old_vect) != 0)
		return (-1);

//	log_print(shell, LOG_INFO, "|%s|%s|\n-----\n", old_vect->buffer, itf->line->buffer);

	ft_asprintf(&concat, "%s%s", old_vect->buffer, itf->line->buffer);

	ft_strdel(&(old_vect->buffer));
	free(old_vect);
	ft_strdel(&(itf->line->buffer));

	itf->line->buffer = concat;
	return (0);
}
