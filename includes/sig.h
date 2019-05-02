/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 18:02:22 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/30 18:13:09 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIG_H
# define SIG_H
void			define_ign_signals(t_registry *shell);
void			define_parser_signals(t_registry *shell);
void			define_execution_signals(t_registry *shell);
void			define_interface_signals(t_registry *shell);
void			define_ign_signals(t_registry *shell);
#endif
