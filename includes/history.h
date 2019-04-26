/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 16:06:08 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/26 13:17:52 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_H
# define HISTORY_H

# define DEFAULT_HISTORY_FILENAME ".sh_history"

typedef struct			s_history
{
	char				*command;
	struct s_history 	*next;
	struct s_history 	*prev;
}						t_history;

t_history				*create_history_entry(char *command);
void					push_history_entry(t_history **head, t_history *node);
#endif
