/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 12:48:35 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/22 07:09:31 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "jobs.h"
#include <fcntl.h>

/*
**
**	Long test is ' ls -Rla /Users/skuppers/skuppers'
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
	filedesc_t	*fd;

	fd = malloc(sizeof(filedesc_t));
	ft_memset(fd, 0, sizeof(filedesc_t));
	head = malloc(sizeof(process_t));
	ft_memset(head, 0, sizeof(process_t));

	head->next = NULL;
	head->av = make_table("/bin/ls", "-l");
	head->pid = -1;
	head->completed = 0;
	head->stopped = 0;
	head->status = 0;
	head->fd = fd;
	head->fd->std_in = 0;
	head->fd->std_out = open("job3file", O_CREAT | O_TRUNC | O_RDWR, 0644);
	head->fd->std_err = 2;

	return (head);
}

static job_t	*ft_newjob(process_t *proc)
{
	job_t	*new;
	filedesc_t	*fd;

	fd = malloc(sizeof(filedesc_t));
	ft_memset(fd, 0, sizeof(filedesc_t));
	new = malloc(sizeof(process_t));
	ft_memset(new, 0, sizeof(process_t));

	new->next = NULL;
	new->command = ft_strdup("/bin/ls -l > job3file");
	new->first_process = proc;
	new->pgid = -1;
	new->term_modes = NULL;
	new->fd = fd;
	new->fd->std_in = 0;
	new->fd->std_out = 1;
	new->fd->std_err = 2;
	return (new);
}


job_t	*get_job3(void)
{
	job_t 		*job;
	process_t	*process;

	job = NULL;
	process = NULL;

	process = ft_new_process();
	job = ft_newjob(process);
	return (job);
}
