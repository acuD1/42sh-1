/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   21sh.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 10:15:10 by skuppers          #+#    #+#             */
/*   Updated: 2019/02/20 14:40:39 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef H_21SH_H
# define H_21SH_H

# include "libft.h"
# include <stdlib.h>

# define WORKSPACE_NAME 	".42sh"
# define KEY_DIRECTORY 		"keymaps"
# define INTERNAL_DIRECTORY "internal"
# define RC_NAME			".42shrc"
# define LOG_FILE	 		"logs"
# define HISTORY_FILE	 	"history"
# define HASH_FILE		 	"hashes"

# define ENV_HOME_NAME "HOME"

# define OPTIONS "cildvn"
# define OPT_C 1
# define OPT_I 2
# define OPT_L 4
# define OPT_D 8
# define OPT_V 16
# define OPT_N 32

typedef struct					s_environment_node
{
	char 						*key;
	char						*value;
	struct s_environment_node	*next;
}								t_environment_node;

typedef struct 					s_registry
{
	unsigned int				arguments;
	unsigned int				live_debug;

	unsigned int				workspace_avaible;
	int							first_time_run;
	
	char						*home_path;
	char						*workspace_path;
	
	t_environment_node			*environment;
}								t_registry;

void	prompt(void);

#endif
