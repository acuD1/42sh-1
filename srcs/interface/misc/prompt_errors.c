/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 14:23:08 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/30 15:41:38 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "log.h"
#include "interface_functions.h"

void	prompt_read_failed(t_registry *reg, t_vector *vect)
{
	log_print(reg, LOG_ERROR, "Prompt read failed!\n");
	ft_strdel(&vect->buffer);
	free(vect);
	vect = NULL;
}
