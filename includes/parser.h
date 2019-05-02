/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 13:39:31 by cempassi          #+#    #+#             */
/*   Updated: 2019/05/02 13:37:34 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "lexer.h"

/*
*****************************************************
****************** STRUCT PARSER ********************
*****************************************************
*/

void		init_parser(t_registry *shell, t_parser *parse);
void		init_process(t_process *process);
void		init_parsing(t_pstate parsing);
t_list		*parser_state(t_pstate parsing, t_parser *parse);
void		separator_parser(t_parser *parse);
void		get_token(t_parser *parse);
void		start_parser(t_parser *parse);
void		string_parser(t_parser *parse);
void		special_string_parser(t_parser *parse);
void		flush_string(t_parser *parse);
void		end_parser(t_parser *parse);
void		error_parser(t_parser *parse);
void		stop_parser(t_parser *parse);
void		redirect_parser(t_parser *parse);
void		pipe_parser(t_parser *parse);
void		filename_state(t_parser *parse);
void		io_parser(t_parser *parse);
void		io_redirect_parser(t_parser *parse);
void		flush_redirect(t_parser *parse);
void		delete_process(void *data);

char		*tilde(t_list *env, char *str);
char		*expand_string(t_list *lst, char *str);

/*
*****************************************************
****************** GRAMMAR PARSER  ******************
*****************************************************
*/

int8_t		parser(t_graph *graph, t_list *lst);
void		generate_graph(t_registry *shell);
void		set_start_token(t_graph *tab_tokens);
void		set_word_token(t_graph *tab_tokens);
void		set_redirect_token(t_graph *tab_tokens);
void		set_assign_token(t_graph *tab_tokens);
void		set_pipe_token(t_graph *tab_tokens);
void		set_ionumber_token(t_graph *tab_tokens);

/*
*****************************************************
*************** GRAMMAR PARSER DEBUG ****************
*****************************************************
*/

void		print_token_debug(t_token *token);
void		print_arrow_debug(int which);
void		print_error_debug(enum e_type type, int which);
void		print_result_debug(int which);

char		character_swap(char swapped);
#endif
