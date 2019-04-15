/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_prompt_len.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 14:12:15 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/15 13:45:24 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"
#include "interface_functions.h"

uint32_t	get_prompt_len(t_registry *shell)
{
	uint32_t	p_len;

	p_len = 0;
	p_len = (uint32_t)ft_strlen(get_intern_var(shell, shell->interface->state));
	return (p_len);
}
