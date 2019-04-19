/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 09:34:25 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/19 14:56:07 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef H_JOBS
# define H_JOBS
#include <termios.h>
#include <unistd.h>

typedef struct			filedesc_s
{
	int32_t				std_in;
	int32_t				std_out;
	int32_t				std_err;
}						filedesc_t;

typedef struct			process_s
{
//	int32_t				ac;

	struct process_s	*next;
	char				**av;
	char				**env;
	pid_t				pid;
	uint8_t				completed;
	uint8_t				stopped;
	int					status;
	filedesc_t			*fd;

}						process_t;

typedef struct			job_s
{

	struct job_s		*next;
	char				*command; /* unused */
	process_t			*first_process;
	pid_t				pgid;
	struct termios		*term_modes;
	filedesc_t			*fd;

}						job_t;

job_t	*get_job1(void); // 		'ls -l 1>file1 | cat -e'
//job_t	*get_job2(void); //			'cat -e | ls -l
//job_t	*get_job3(void); //			'/bin/ls -Rla /Users/skuppers '

job_t	*g_job_head;


void	fork_child(job_t *job, process_t *process, char **env, filedesc_t fd);

job_t		*find_job(pid_t pgid);
uint8_t		job_is_stopped(job_t *job);
uint8_t		job_is_completed(job_t *job);
#endif
