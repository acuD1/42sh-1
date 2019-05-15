/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <skuppers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 14:49:54 by skuppers          #+#    #+#             */
/*   Updated: 2019/05/07 16:54:02 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface_functions.h"

#include "sh21.h"

#include <sys/ioctl.h>

/////////////////////////////////////////////////





uint64_t	update_winsize(t_registry *shell)
{
	struct winsize w;
	t_window		*win;

    win = &shell->interface.window;
	if (ioctl(STDIN_FILENO, TIOCGWINSZ, &w) == FAILURE)
        return (CRITICAL_ERROR | WINDOW_FAIL);

	win->rows = (w.ws_row <= 0) ? 0 : w.ws_row;
	win->cols = (w.ws_col <= 0) ? 0 : w.ws_col;
    win->max_chars = win->rows * win->cols;
	
    if (add_internal_nbr(shell, INT_COLS, win->cols) == FAILURE)
		return (WINDOW_FAIL | INTERNAL_FAIL);

	if (add_internal_nbr(shell, INT_ROWS, win->rows) == FAILURE)
		return (WINDOW_FAIL | INTERNAL_FAIL);

	return (SUCCESS);
}

void	update_window(t_registry *shell)
{
	update_winsize(shell);

	shell->interface.cursor.x = 0;
	shell->interface.cursor.y = 0;
	shell->interface.cursor.index = 0;
}




////////////////////////////////////////////////////





static void		print_loop(t_interface *itf, char *str)
{
	while (*str != '\0')
	{
		write(1, *str, 1);
		++str;
		itf->cursor.x++;
		if (itf->cursor.x == itf->window.cols)
		{
			itf->cursor.y++;
			itf->cursor.x = 0;
		}
	}
}

void	print_to_window(t_interface *itf, t_vector *text)
{
	if (vct_len(text) < itf->window.max_chars)
		print_loop(&itf->window, vct_get_string(text));
	else if (itf->window.max_chars > 1)
		print_loop(&itf->window, ">");
}






////////////////////////////////////////////










void	expand_prompt(t_vector *text)
{
	//read the text
	// parse \t \u \h \H \w \W \d \m
	// insert the corresponding string into
}


static inline void		print_prompt(t_registry *shell, char *state)
{
	t_vector	*ptext;

	ptext = NULL;

	ptext = vct_dups(get_intern_var(shell, state));
	if (ptext == NULL)
		ptext = vct_dups("42sh -> ");

	expand_prompt(ptext);
	print_to_window(&shell->interface, ptext);

	shell->interface.window.prompt.text = ptext;
}




////////////////////////////////////////////////////////




static inline uint8_t	is_separator(char character[READ_SIZE + 1])
{
	if (character[0] == IFS_CHAR)
		return (TRUE);
	return (FALSE);
}



/*
**	Standart prompt invocation
**
**
*/

t_vector	*prompt(t_registry *shell, char *prompt_state)
{
	char	character[READ_SIZE + 1];

	update_window(&shell->interface.window);
	print_prompt(shell, prompt_state);
	
	ft_bzero(character, READ_SIZE + 1);

	while (!is_separator(character))
	{
		ft_bzero(character, READ_SIZE);

		if (read(0, character, READ_SIZE) == FAILURE)
			return (NULL);
		
		handle_input_key(shell, character);
		redraw(shell);

		if (is_eof(shell->interface.line))
			break ;
	}

	overwrite_protection(shell);

	return (vct_dup(shell->interface.line));
}

/*
**	Sub prompt invokation.
**	Prompt_state is between INT_PS1 & INT_PS4, missing is \m
**	Returns an allocated vector
**	Return NULL on read error, eof, or dup error(malloc)
*/
t_vector	*sub_prompt(t_registry *shell,
					char *prompt_state, char *missing)
{
	t_vector	*linesave;

	linesave = shell->interface.line;
	shell->interface.line = shell->interface.sub_line;


	prompt(shell, prompt_state);

	shell->interface.line = linesave;
	
	if (is_eof(shell->interface.sub_line))
		return (NULL);

	return (vct_dup(shell->interface.sub_line));
}