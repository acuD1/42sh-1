/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 14:49:54 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/30 16:55:49 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface_functions.h"
#include "log.h"
#include "ft_printf.h"
#include "history.h"
#include "builtin.h"
#include "21sh.h"
#include <unistd.h>

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
	char			*prompt;

	prompt = NULL;
	pwd = get_pwd(shell, NO_OPT);
	if (pwd != NULL)
		pwd = get_last_directory_of_pwd(&pwd);
	if (pwd == NULL)
		add_internal(shell, "PS1", "[21sh] -> ");
	else
	{
		ft_asprintf(&prompt, "[ \033[32m%s\033[0m ] -> ", pwd);
		ft_strdel(&pwd);
		add_internal(shell, "PS1", prompt);
		ft_strdel(&prompt);
	}
}

char			*prompt(t_registry *shell)
{
	char			character[READ_SIZE + 1];
	t_interface 	*itf;

	itf = &shell->interface;
	ft_bzero(character, READ_SIZE);
	ft_dprintf(STDOUT_FILENO, "\n%s", get_intern_var(shell, itf->state));
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
