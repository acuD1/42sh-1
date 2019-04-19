/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   registry.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 22:51:23 by cempassi          #+#    #+#             */
/*   Updated: 2019/04/20 00:52:39 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REGISTRY_H
# define REGISTRY_H
# include "libft.h"
# include "line_edit.h"

typedef struct s_interface	t_interface;
typedef struct s_registry	t_registry;

typedef struct s_opt
{
	int		h;
	int		v;
	int		d;
	int		c;
	int		norc;
	int		rcfile;
	char	*cmd;
	char	*path;
}				t_opt;

struct						s_interface
{
	t_vector				*line;
	t_vector				*clip;
	t_cursor				*cursor;
	t_window				*window;
	t_termcaps				*termcaps;

	char					*state;
	unsigned long			ak_masks[AK_AMOUNT];
	int8_t					(*tc_call[AK_AMOUNT])(struct s_registry *shell);
};

struct		s_registry
{
	t_opt			option;
	t_list			*env;
	t_list			*intern;
	t_hash			bin_hashmap;
	t_hash			blt_hashmap;
	t_interface		interface;
};

#endif
