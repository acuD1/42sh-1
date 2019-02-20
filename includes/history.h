/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 16:06:08 by skuppers          #+#    #+#             */
/*   Updated: 2018/12/18 16:15:04 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_H
# define HISTORY_H

# define DEFAULT_HISTORY_FILENAME ".42sh_history"

typedef struct			s_history
{
	unsigned int		ID;
	char				*command;
	struct s_history 	*next;
	struct s_history 	*prev;
}						t_history;

extern	t_history		*g_history_head;
extern	t_history		*g_history_selection;

t_history				*create_history_entry(char *command);
t_history				*get_history_entry();
void					push_history_entry(t_history **head, t_history *node);

int						write_history_to_file(t_history *last);
t_history				*load_history_from_file(void);

#endif
