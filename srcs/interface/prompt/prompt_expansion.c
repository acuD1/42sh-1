/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_expansion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 17:53:07 by skuppers          #+#    #+#             */
/*   Updated: 2019/05/27 09:37:20 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "interface_functions.h"

void		p_insert_color(t_vector *text, uint64_t index)
{
	if (vct_charat(text, index + 1) == 'n')
		vct_replace_string(text, index - 1, index + 2, ESC_COLOR_NO);
	else if (vct_charat(text, index + 1) == 'r')
		vct_replace_string(text, index - 1, index + 2, ESC_COLOR_RED);
	else if (vct_charat(text, index + 1) == 'g')
		vct_replace_string(text, index - 1, index + 2, ESC_COLOR_GREEN);
	else if (vct_charat(text, index + 1) == 'b')
		vct_replace_string(text, index - 1, index + 2, ESC_COLOR_BLUE);
	else if (vct_charat(text, index + 1) == 'y')
		vct_replace_string(text, index - 1, index + 2, ESC_COLOR_YELLOW);
	else if (vct_charat(text, index + 1) == 'p')
		vct_replace_string(text, index - 1, index + 2, ESC_COLOR_PURPLE);
}

void		p_insert_name(t_vector *text, uint64_t index)
{
	vct_replace_string(text, index, index + 2, "42sh");
}

void		p_insert_username(t_registry *shell, t_vector *text, uint64_t index)
{
	char	*username;

	username = get_env_var(shell, "USER");
	if (username == NULL)
		username = ft_strdup("user");
	vct_replace_string(text, index, index + 2, username);
}

void		p_insert_cwd(t_registry *shell, t_vector *text, uint64_t index)
{
	size_t	len;
	char	*cwd;
	char	*home;

	len = 0;
	cwd = get_env_var(shell, "PWD");
	if (cwd == NULL)
		cwd = ft_strdup("working-dir");
	vct_replace_string(text, index, index + 2, cwd);
	if ((home = get_env_var(shell, "HOME")) != NULL)
	{
		if (ft_strbeginswith(cwd, home))
		{
			len = ft_strlen(home);
			vct_replace_string(text, index, index + len, "~");
		}
	}
}

void		p_insert_host(__unused t_registry *shell,
				t_vector *text,
				uint64_t index)
{
	char	*host;
	char	*hostname;
	size_t	host_len;

	host_len = 32;
	host = ft_strnew(host_len);
	gethostname(host, host_len);
	hostname = NULL;
	if (gethostname(host, host_len) != 0)
		hostname = ft_strdup("hostname");
	else
		hostname = ft_strsub(host, 0, ft_strcspn(host, "."));
	ft_strdel(&host);
//	ft_strdel(&hostname);
	vct_replace_string(text, index, index + 2, hostname);
}
