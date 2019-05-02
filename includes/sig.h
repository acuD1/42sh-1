/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 18:02:22 by skuppers          #+#    #+#             */
/*   Updated: 2019/05/02 11:54:19 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIG_H
# define SIG_H

void	define_ign_signals(void);
void	define_parser_signals(void);
void	define_execution_signals(void);
void	define_interface_signals(void);
void	define_default_signals(void);

#endif
