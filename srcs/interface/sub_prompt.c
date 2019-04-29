/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_shell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 00:22:47 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/27 15:47:32 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "log.h"
#include "interface_functions.h"

static void			print_sub_prompt(t_registry *shell)
{
	shell->interface.cursor.x = 0;
	shell->interface.cursor.y = 0;
	ft_printf("\n");
	//protect intern_var call and set to 'sub'
	print_words(&shell->interface, 
				get_intern_var(shell, shell->interface.state));
	shell->interface.cursor.index = 0;
}

static int8_t		sub_prompt_loop(t_registry *shell, t_interface *itf)
{
	char		character[READ_SIZE + 1];

	ft_bzero(character, READ_SIZE + 1);
	while (character[0] != IFS_CHAR)
	{
		ft_bzero(character, READ_SIZE);
		if (read(0, character, READ_SIZE) == FAILURE)
		{
			prompt_read_failed(shell, itf->line);
			return (-2);
		}
		handle_input_key(shell, character);
		if (is_eof(itf->line->buffer) == TRUE)
		{
//			ft_strdel(&(itf->line->buffer));
//			free(itf->line);
//			itf->line = ft_vctnew(0);
			return (-4);
		}
	}
	return (SUCCESS);
}
/*
static int8_t		is_std_ps(char *p_state)
{
	if (ft_strequ(p_state, INT_PS1)
		|| ft_strequ(p_state, INT_PS2)
		|| ft_strequ(p_state, INT_PS3)
		|| ft_strequ(p_state, INT_PS4))
		return (TRUE);
	return (FALSE);
}
*/
int8_t				invoke_sub_prompt(t_registry *shell, char **line,
						char *prompt_state)
{
	t_interface		*itf;

	itf = &shell->interface;
	
//	if (is_std_ps(prompt_state) == FALSE)
//		add_internal(shell, INT_PS5, prompt_state);
	itf->state = prompt_state;

	if (validate_interface_content(itf) == FAILURE)
		return (FAILURE);

	reset_vector(itf->line);
	print_sub_prompt(shell);
	if (sub_prompt_loop(shell, itf) != SUCCESS)
	{
		*line = NULL;
		reset_vector(itf->line);
		ft_strdel(&(itf->line->buffer));
		return (FAILURE);
	}
	*line = ft_strdup(itf->line->buffer);
	ft_strdel(&(itf->line->buffer));
	reset_vector(itf->line);
	return (SUCCESS);
}
