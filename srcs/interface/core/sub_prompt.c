/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_shell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 00:22:47 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/09 19:12:00 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "log.h"
#include "line_edit.h"

static void		print_ps2_prompt(t_interface_registry *itf)
{
	itf->window->x = 0;
	itf->window->y = 0;
	ft_printf("\n");
	print_words(get_intern_var(itf->sh_reg, INT_PS2), itf);
	itf->window->cursor = 0;
}

static t_vector	*create_ps2_vect(t_interface_registry *itf)
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

static int		ps2_prompt_loop(t_registry *shell,
				t_interface_registry *itf, t_vector *old_vect)
{
	char		ifs_char;
	char		character[READ_SIZE + 1];

	ifs_char = 0;
	ifs_char = ft_atoi(get_intern_var(shell, INT_IFS));
	ft_bzero(character, READ_SIZE + 1);
	while (character[0] != ifs_char)
	{
		ft_bzero(character, READ_SIZE);
		if (read(0, character, READ_SIZE) == -1)
		{
			prompt_read_failed(shell, itf->line);
			return (-2);
		}
		handle_input_key(character, itf);
		if (itf->line->buffer[0] == 4)
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

int				invoke_ps2_prompt(t_registry *shell,
				t_interface_registry *itf)
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
	log_print(shell, LOG_INFO, "|%s|%s|\n-----\n", old_vect->buffer, itf->line->buffer);
	ft_asprintf(&concat, "%s%s", old_vect->buffer, itf->line->buffer);
	ft_strdel(&(old_vect->buffer));
	free(old_vect);
	ft_strdel(&(itf->line->buffer));
	itf->line->buffer = concat;
	return (0);
}
