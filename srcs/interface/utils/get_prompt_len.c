/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_prompt_len.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 14:12:15 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/27 15:50:32 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface_functions.h"

uint32_t	get_prompt_len(t_registry *shell)
{
	uint32_t	p_len;

	p_len = 0;
	p_len = (uint32_t)ft_strlen(get_intern_var(shell, shell->interface->state));
	return (p_len);
}
