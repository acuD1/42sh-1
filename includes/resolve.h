/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 13:13:50 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/23 19:14:53 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef H_RESOLVE_H
#define H_RESOLVE_H

#include <termios.h>
#include <unistd.h>
#include "21sh.h"
#include "parser.h"

extern t_list	*g_job_head;

void					launch_job(t_registry *shell, t_list *joblst);

void					setup_pipes(t_job *j, t_list *p, t_filedesc *io, int pipe[2]);
void					cleanup_pipes(t_job *job, t_filedesc *io);
void					link_pipes(t_list *process, t_filedesc *io, int my_pipe[2]);

void					launch_process(t_job *job, t_process *process,
				t_registry *shell, t_filedesc *io);

void					wait_for_job(t_job *job);

/* Job tools */
t_job					*find_job(pid_t pid);
uint8_t					job_is_stopped(t_job *job);
uint8_t					job_is_completed(t_job *job);

#endif