/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 12:35:05 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/19 14:22:58 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "jobs.h"

/*
**
**	First test is ' ls -l | cat -e '
**
*/

static char **make_table(char *av1, char *av2)
{
	char	**new;

	new = malloc(sizeof(char*) * 3);
	ft_memset(new, 0, sizeof(char*) * 3);
	new[0] = ft_strdup(av1);
	new[1] = ft_strdup(av2);
	return (new);
}

static process_t	*ft_new_process()
{
	process_t	*head;
	process_t	*new;

	new = malloc(sizeof(process_t));
	ft_memset(new, 0, sizeof(process_t));

	new->next = NULL;
	new->av = make_table("/bin/ls", "-l");
	new->pid = -1;
	new->completed = 0;
	new->stopped = 0;
	new->status = 0;
//	new->fdin = 0;
//	new->fdout = 1;
//	new->fderr = 2;

	head = malloc(sizeof(process_t));
	ft_memset(head, 0, sizeof(process_t));

	head->next = new;
	head->av = make_table("/bin/cat", "-e");
	head->pid = -1;
	head->completed = 0;
	head->stopped = 0;
	head->status = 0;
//	head->fdin = 0;
//	head->fdout = 1;
//	head->fderr = 2;

	return (head);
}

static job_t	*ft_newjob(process_t *proc)
{
	job_t	*new;

	new = malloc(sizeof(process_t));
	ft_memset(new, 0, sizeof(process_t));
	new->next = NULL;
	new->command = ft_strdup("/bin/cat -e | /bin/ls -l");
	new->first_process = proc;
	new->pgid = -1;
	new->term_modes = NULL;
//	new->fdin = 0;
//	new->fdout = 1;
//	new->fderr = 2;
	return (new);
}


job_t	*get_job2(void)
{
	job_t 		*job;
	process_t	*process;

	job = NULL;
	process = NULL;

	process = ft_new_process();
	job = ft_newjob(process);
	return (job);
}
