/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 14:23:08 by skuppers          #+#    #+#             */
/*   Updated: 2019/02/27 11:49:42 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#include "line_edit.h"
#include "log.h"

void	prompt_read_failed(t_registry *reg, t_vector *vect)
{
	log_print(reg, LOG_ERROR, "Prompt read() failed!\n");
	ft_strdel(&(vect->buffer));
	free(vect);
	vect = NULL;
}
