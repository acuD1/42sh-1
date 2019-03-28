/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   21sh.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 10:15:10 by skuppers          #+#    #+#             */
/*   Updated: 2019/03/28 18:42:02 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH21_H
# define SH21_H

// debug_file_name  - nom du fichier de debug -> ".42sh_debug.log"
// debug_fd 	    - file descriptor du fichier de debug
// ws.cols
// ws.rows

typedef struct s_registry
{
	int	debug_fd;
}			t_registry;

void	shell_invoke_interactive(t_registry *reg);

#endif
