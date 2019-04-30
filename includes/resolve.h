/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 13:13:50 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/30 11:37:54 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef H_RESOLVE_H
#define H_RESOLVE_H

#include <termios.h>
#include <unistd.h>
#include "21sh.h"
#include "parser.h"
# include "define.h"
# include "struct.h"

void		define_execution_signals(t_registry *shell);

void		launch_job(t_registry *shell, t_list *joblst);
void		setup_pipes(t_job *j, t_list *p, t_filedesc *io, int pipe[2]);
void		cleanup_pipes(t_job *job, t_filedesc *io);
void		link_pipes(t_list *process, t_filedesc *io, int my_pipe[2]);
int			launch_process(t_job *job, t_process *process, t_registry *shell);
void		wait_for_job(t_job *job);
uint8_t		job_is_stopped(t_job *job);
uint8_t		job_is_completed(t_job *job);

#endif
