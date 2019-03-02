/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   21sh.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 10:15:10 by skuppers          #+#    #+#             */
/*   Updated: 2019/03/02 11:08:53 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef H_21SH_H
# define H_21SH_H

# include "libft.h"
# include <stdlib.h>
# include <unistd.h>

# define WORKSPACE_NAME 	".42sh"
# define KEY_DIRECTORY 		"keymaps"
# define INTERNAL_DIRECTORY "internal"
# define RC_NAME			".42shrc"
# define LOG_FILE	 		"logs"
# define HISTORY_FILE	 	"history"
# define HASH_FILE		 	"hashes"

# define ENV_HOME_NAME "HOME"

# define ENV_SEPARATOR '='

typedef struct					s_environment_node
{
	char 						*key;
	char						*value;
	struct s_environment_node	*next;
}								t_environment_node;

typedef struct					s_arguments
{
	unsigned short				opt_c;
	unsigned short				opt_i;
	unsigned short				opt_l;
	unsigned short				opt_d;
	unsigned short				opt_v;
	unsigned short				opt_n;
	unsigned short				opt_h;
	unsigned short				opt_posix;
	unsigned short				opt_norc;
	unsigned short				opt_rcfile;
	char						*rcfile_path;
	char						*c_param;
}								t_arguments;

typedef struct 					s_registry
{
	t_arguments					*arguments;
	unsigned int				workspace_avaible;
	char						*home_path;
	char						*workspace_path;

	int							debug_fd;

	
	t_environment_node			*environment;
}								t_registry;

char	*get_env_node_value(t_environment_node *head, char *key);
void	cleanup_shell_registry(t_registry *shell_reg);
#endif
