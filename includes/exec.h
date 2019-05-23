/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 12:41:26 by cempassi          #+#    #+#             */
/*   Updated: 2019/05/23 16:34:18 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H
# include "21sh.h"

void		signal_job(void);
void		signal_ignore(void);
void		signal_execution(void);
int			execute_pid(t_process *process);
void		fork_process(void *data);
int			run_builtin(t_process *process);
int			run_job(t_registry *shell);
int			check_completed(t_list *lst);
void		delete_finished(t_process *process, int status);
void		wait_job(t_registry *shell);
int			check_to_close(void *data, void *to_test);
int			find_process(void *data, void *to_find);
#endif
