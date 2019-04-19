/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 12:48:35 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/19 14:23:14 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "jobs.h"

/*
**
**	Long test is ' ls -Rla /Users/skuppers/skuppers'
**
*/

static char **make_table(char *av1, char *av2, char *av3)
{
	char	**new;

	new = malloc(sizeof(char*) * 4);
	ft_memset(new, 0, sizeof(char*) * 4);
	new[0] = ft_strdup(av1);
	new[1] = ft_strdup(av2);
	new[2] = ft_strdup(av3);
	return (new);
}

static process_t	*ft_new_process()
{
	process_t	*head;

	head = malloc(sizeof(process_t));
	ft_memset(head, 0, sizeof(process_t));

	head->next = NULL;
	head->av = make_table("/bin/ls", "-Rla", "/Users/skuppers/42sh");
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
	new->command = ft_strdup("/bin/ls -Rla /Users/skuppers/42sh");
	new->first_process = proc;
	new->pgid = -1;
	new->term_modes = NULL;
//	new->fdin = 0;
//	new->fdout = 1;
//	new->fderr = 2;
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
