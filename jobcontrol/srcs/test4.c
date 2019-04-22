/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 07:17:31 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/22 13:18:34 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "jobs.h"
#include <fcntl.h>

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
	filedesc_t	*fd1;
	filedesc_t	*fd2;

	new = malloc(sizeof(process_t));
	ft_memset(new, 0, sizeof(process_t));

	fd1 = malloc(sizeof(filedesc_t));
	ft_memset(fd1, 0, sizeof(filedesc_t));
	fd2 = malloc(sizeof(filedesc_t));
	ft_memset(fd2, 0, sizeof(filedesc_t));

	new->next = NULL;
	new->av = make_table("/bin/cat", "-e");
	new->pid = -1;
	new->completed = 0;
	new->stopped = 0;
	new->status = 0;
	fd1->std_in = 0;
	fd1->std_out = 1;
	fd1->std_err = 2;
	new->fd = fd1;

	head = malloc(sizeof(process_t));
	ft_memset(head, 0, sizeof(process_t));

	head->next = new;
	head->av = make_table("/bin/ls", "-l");
	head->pid = -1;
	head->completed = 0;
	head->stopped = 0;
	head->status = 0;
	fd2->std_in = 0;
	fd2->std_out = open("file4", O_CREAT | O_TRUNC | O_RDWR, 0644);
	fd2->std_err = 2;
	head->fd = fd2;

	return (head);
}

static job_t	*ft_newjob(process_t *proc)
{
	job_t		*new;
	filedesc_t	*fd;

	new = malloc(sizeof(process_t));
	ft_memset(new, 0, sizeof(process_t));
	fd = malloc(sizeof(filedesc_t));
	ft_memset(fd, 0, sizeof(filedesc_t));

	new->next = NULL;
	new->command = ft_strdup("/bin/ls -l > file4 | cat -e");
	new->first_process = proc;
	new->pgid = -1;
	new->term_modes = NULL;
	new->fd = fd;
	fd->std_in = 0;
	fd->std_out = 1;
	fd->std_err = 2;
	return (new);
}


job_t	*get_job4(void)
{
	job_t 		*job;
	process_t	*process;

	job = NULL;
	process = NULL;

	process = ft_new_process();
	job = ft_newjob(process);
	return (job);
}

