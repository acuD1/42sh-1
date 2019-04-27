/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 14:21:32 by ffoissey          #+#    #+#             */
/*   Updated: 2019/04/27 16:20:37 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "libft.h"
# include "define.h"
# include "struct.h"

t_list		*lexer(char *input);
void		start_lexer(t_lexer *machine);
void		end_machine(t_lexer *machine);
void		out_lexer(t_lexer *machine);
void		letter_machine(t_lexer *machine);
void		number_machine(t_lexer *machine);
void		sign_machine(t_lexer *machine);
void		expansion_machine(t_lexer *machine);
void		backslash_machine(t_lexer *machine);
void		single_quote_machine(t_lexer *machine);
void		double_quote_machine(t_lexer *machine);
void		double_sign_machine(t_lexer *machine);
void		greater_machine(t_lexer *machine);
void		lesser_machine(t_lexer *machine);
void		greatand_machine(t_lexer *machine);
void		tilde_machine(t_lexer *machine);
void		fill_buffer_output(t_lexer *machine);
t_token 	generate_token(t_lexer *machine);

/*
*****************************************************
******************* TEMP DISPLAY ********************
*****************************************************
*/

void	print_token(t_list *list);
void	del_token(void *token);

#endif
