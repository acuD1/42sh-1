/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 14:49:54 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/30 20:11:34 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface_functions.h"
#include "log.h"
#include "ft_printf.h"
#include "history.h"
#include "builtin.h"

static char		*get_last_directory_of_pwd(char **pwd)
{
	char	*last_dir;
	char	*ptr_last_slash;
	size_t	len_pwd;

	last_dir = NULL;
	len_pwd = ft_strlen(*pwd);
	if (ft_strequ(*pwd, "/") == TRUE)
	{
		last_dir = ft_strdup(*pwd);
		ft_strdel(pwd);
		return (last_dir);
	}
	if ((*pwd)[len_pwd - 1] == '/')
		(*pwd)[len_pwd - 1] = '\0';
	if ((ptr_last_slash = ft_strrchr(*pwd, '/')) != NULL)
		last_dir = ft_strdup(ptr_last_slash + 1);
	ft_strdel(pwd);
	return (last_dir);
}

void			get_prompt_ps1(t_registry *shell)
{
	char			*pwd;
	t_interface 	*itf;
	char			*state;

	itf = &shell->interface;
	state = get_intern_var(shell, itf->state);
	pwd = get_pwd(shell, NO_OPT);
	if (pwd != NULL)
		pwd = get_last_directory_of_pwd(&pwd);
	if (pwd == NULL)
		add_internal(shell, INT_PS1, INT_PS1_VALUE);
	else
	{
		add_internal(shell, INT_PS1, pwd);
		ft_strdel(&pwd);
	}
}

static void		print_prompt(t_registry *shell)
{
	t_interface 	*itf;
	char			*prompt;

	itf = &shell->interface;
	prompt = get_intern_var(shell, itf->state);
	if (ft_strequ(prompt, INT_PS1_VALUE) == TRUE
		|| ft_strequ(prompt, INT_PS2_VALUE) == TRUE
		|| ft_strequ(prompt, INT_PS3_VALUE) == TRUE
		|| ft_strequ(prompt, INT_PS4_VALUE) == TRUE)
		ft_dprintf(STDOUT_FILENO, "\n%s", prompt);
	else
		ft_dprintf(STDOUT_FILENO, "\n[ \033[32m%s\033[0m ] -> ", prompt);
}

char			*prompt(t_registry *shell)
{
	char			character[READ_SIZE + 1];
	t_interface 	*itf;

	itf = &shell->interface;
	ft_bzero(character, READ_SIZE);
	print_prompt(shell);
	itf->hist_ptr = NULL;
	while (character[0] != IFS_CHAR)
	{
		ft_bzero(character, READ_SIZE);
		// change to tty fd
		if (read(0, character, READ_SIZE) == FAILURE)
		{
			prompt_read_failed(shell, itf->line);
			return (NULL);
		}
		handle_input_key(shell, character);
		if (is_eof(itf->line->buffer) == TRUE)
			return (itf->line->buffer);
	}
	tc_ak_end(shell);
	validate_input_quoting(shell, itf);
	return (itf->line->buffer);
}
