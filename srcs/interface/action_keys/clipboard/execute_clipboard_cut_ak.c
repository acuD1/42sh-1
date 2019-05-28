/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_clipboard_cut_ak.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 10:41:35 by skuppers          #+#    #+#             */
/*   Updated: 2019/05/28 09:25:28 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface_functions.h"
#include "log.h"

int8_t				ak_cut_selection(t_registry *shell)
{
	char			*tmp;
	t_interface		*itf;

	itf = &shell->interface;
	if (itf->visual_mode == FALSE)
		return (FAILURE);

	log_print(shell, LOG_INFO, "Idx: %d Len : %d\n", itf->vis_start,
					itf->vis_stop);

	tmp = vct_sub(itf->line, itf->vis_start,
					(itf->vis_stop - itf->vis_start) + 1);
	vct_scpy(itf->clip, tmp, ft_strlen(tmp));
	ft_strdel(&tmp);
	log_print(shell, LOG_INFO, "Cut |%s| to clipboard.\n",
					vct_get_string(itf->clip));
	return (SUCCESS);
}
