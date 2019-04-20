/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 15:41:22 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/20 05:11:17 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"
#include "interface_functions.h"

int8_t	init_cursor(t_registry *shell)
{
	shell->interface.cursor.index = 0;
	shell->interface.cursor.x = get_prompt_len(shell);
	shell->interface.cursor.y = 0;
	return (0);
}
