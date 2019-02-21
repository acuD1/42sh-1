/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   startup_initialisation.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 14:33:03 by skuppers          #+#    #+#             */
/*   Updated: 2019/02/21 13:22:48 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "startup.h"

/* If invoked as interactive login shell or non-interactive login shell:
	 * -> reads and executes /etc/profile if it exist.
	 * -> reads ~/.bash_profile, ~/.bash_login, ~/.profile if exist.
	 * '--noprofile' inhibits this behavior.
	 *  At Exit() it reads and executes ~/.bash_logout, if it exist.
	 *
	 * If invoked as non-login interactive shell,
	 * it reads and executes ~/.bashrc if it exists
	 * which can be inhibited with the '--norc' option or forces
	 * the file to be read to be 'file' with the option '--rcfile a_file'
	 *
	 * Search and exec {/etc/profile, /etc/paths.d/,  /etc/manpaths
*/
void	load_config_files(t_registry *reg)
{
 //TODO: load and exec file according to launch arguments
}
