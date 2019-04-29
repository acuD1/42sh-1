/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 13:19:49 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/27 16:35:05 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "21sh.h"

char		*ft_strjoinfree(char *s1, char *s2, short todel)
{
	char	*join;

	if (!(join = ft_strnew(ft_strlen(s1) + ft_strlen(s2))))
		return (NULL);
	ft_strcpy(join, s1);
	ft_strcat(join, s2);
	if (todel == 1)
		ft_strdel(&s1);
	return (join);
}

char	*read_input(int fd)
{
	char	*final;
	char	buffer[16];

	final = NULL;
	ft_memset(buffer, 0, 16);
	while (read(fd, buffer, 15) > 0)
	{
		if (final == NULL)
			final = ft_strdup(buffer);
		else
			final = ft_strjoinfree(final, buffer, 1);
		ft_memset(buffer, 0, 16);
	}
	return (final);
}