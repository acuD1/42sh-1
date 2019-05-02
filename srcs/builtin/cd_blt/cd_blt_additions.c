/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_blt_additions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 18:11:50 by ffoissey          #+#    #+#             */
/*   Updated: 2019/04/30 16:24:49 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "21sh.h"
#include <unistd.h>
#include <pwd.h>

t_option		get_option_cd(char *s, t_option option)
{
	option = 0;
	while (*s)
	{
		if (*s == 'L')
			option |= L_OPT;
		else if (*s == 'P')
			option |= P_OPT;
		else
		{
			ft_dprintf(2, "21sh: cd: -%c: invalid option\n", *s);
			ft_dprintf(2, CD_USAGE);
			return (ERROR_OPT);
		}
		s++;
	}
	return (option);
}

int8_t			exit_cd(t_registry *shell, char **old_pwd,
					char **curpath, int8_t ret)
{
	ft_strdel(old_pwd);
	ft_strdel(curpath);
	if (ret == SUCCESS)
		get_prompt_ps1(shell);
	return (ret);
}

char			*concat_pwd_with_curpath(t_registry *shell, char **path)
{
	char	*curpath;
	char	*pwd;
	char	*tmp_pwd;

	pwd = get_pwd(shell, NO_OPT);
	if (pwd == NULL)
		return (NULL);
	else if (pwd[ft_strlen(pwd) - 1] != '/')
	{
		tmp_pwd = pwd;
		pwd = ft_strjoin(pwd, "/");
		ft_strdel(&tmp_pwd);
	}
	curpath = ft_strjoin(pwd, *path);
	ft_strdel(path);
	ft_strdel(&pwd);
	return (curpath);
}

char			*get_home_path(void)
{
	struct passwd	*pwd;
	char			*home_path;

	pwd = getpwuid(geteuid());
	home_path = pwd->pw_dir;
	return (home_path);
}

char			*get_relative_path(char **curpath)
{
	char	*pwd;
	char	*new_path;

	pwd = NULL;
	pwd = getcwd(NULL, PATH_MAX);
	if (ft_strstr(*curpath, pwd) != NULL)
		new_path = ft_strdup(*curpath + ft_strlen(pwd) + 1);
	else
		return (*curpath);
	ft_strdel(curpath);
	return (new_path);
}
