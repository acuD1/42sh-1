/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   registry.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 22:51:23 by cempassi          #+#    #+#             */
/*   Updated: 2019/04/23 20:48:11 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REGISTRY_H
# define REGISTRY_H
# include "libft.h"
# include "line_edit.h"

typedef struct s_interface	t_interface;
typedef struct s_registry	t_registry;
typedef unsigned long		t_key_mask[AK_AMOUNT];
typedef int8_t				(*t_key_call)(t_registry *);

typedef struct	s_opt
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

struct			s_interface
{
	struct termios	*term_mode;
	struct termios	*orig_mode;
	t_cursor	cursor;
	t_window	window;
	t_termcaps	termcaps;
	t_vector	*line;
	t_vector	*clip;
	char		*state;
	t_key_mask	ak_masks;
	t_key_call	tc_call[AK_AMOUNT];
};

struct			s_registry
{
	t_opt			option;
	t_list			*env;
	t_list			*intern;
	t_list			*job_list;
	t_hash			bin_hashmap;
	t_hash			blt_hashmap;
	t_interface		interface;
};

#endif
