/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 13:39:31 by cempassi          #+#    #+#             */
/*   Updated: 2019/04/30 16:14:18 by cempassi         ###   ########.fr       */
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
void		flush_string(t_parser *parse);
void		end_parser(t_parser *parse);
void		error_parser(t_parser *parse);
void		stop_parser(t_parser *parse);
void		single_quote_parser(t_parser *parse);
void		redirect_parser(t_parser *parse);
void		pipe_parser(t_parser *parse);
void		filename_state(t_parser *parse);
void		io_redirect_parser(t_parser *parse);
void		flush_redirect(t_parser *parse);
void		delete_process(void *data);


/*
*****************************************************
****************** GRAMMAR PARSER  ******************
*****************************************************
*/

int			parser(t_graph *graph, t_list *lst);
void		generate_graph(t_registry *shell);
void		set_start_token(t_graph *tab_tokens);
void		set_word_token(t_graph *tab_tokens);
void		set_redirect_token(t_graph *tab_tokens);
void		set_assign_token(t_graph *tab_tokens);
void		set_pipe_token(t_graph *tab_tokens);
void		set_ionumber_token(t_graph *tab_tokens);

/*
**	void		set_if_token(t_graph **graph);
**	void		set_elif_token(t_graph **graph);
**	void		set_else_token(t_graph **graph);
**	void		set_then_token(t_graph **graph);
**	void		set_fi_token(t_graph **graph);
**	void		set_bracket_open_token(t_graph **graph);
**	void		set_bracket_close_token(t_graph **graph);
**	void		set_pipe_token(t_graph **graph);
*/

/*
*****************************************************
*************** GRAMMAR PARSER DEBUG ****************
*****************************************************
*/

void		print_token_debug(t_token *token);
void		print_arrow_debug(int which);
void		print_error_debug(enum e_type type, int which);
void		print_result_debug(int which);

#endif
