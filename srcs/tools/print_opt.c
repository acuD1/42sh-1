/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   21sh.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 13:17:19 by nrechati          #+#    #+#             */
/*   Updated: 2019/04/27 16:24:38 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "21sh.h"
#include "log.h"

void	print_opt(t_registry *shell)
{
	log_print(shell, LOG_INFO, "Options: \n");
	log_print(shell, LOG_INFO, "| h=%d | v=%d | d=%d |\n",
				(shell->option.option & HELP_OPT) == FALSE ? 0 : 1,
				(shell->option.option & VERSION_OPT) == FALSE ? 0 : 1,
				(shell->option.option & DEBUG_OPT) == FALSE ? 0 : 1);
	log_print(shell, LOG_INFO, "| c=%d | cmd=%s |\n",
				(shell->option.option & COMMAND_OPT) == FALSE ? 0 : 1,
				shell->option.command_str);
}
