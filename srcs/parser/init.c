/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 21:57:35 by cempassi          #+#    #+#             */
/*   Updated: 2019/04/23 15:37:43 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	init_start(t_parser *parse)
{
	parse->parsing[P_START][E_STRING] = string_parser;
	parse->parsing[P_START][E_QUOTE] = single_quote_parser;
	parse->parsing[P_START][E_GREAT] = redirect_parser;
	parse->parsing[P_START][E_LESS] = redirect_parser;
	parse->parsing[P_START][E_DGREAT] = redirect_parser;
	parse->parsing[P_START][E_IO_NUMBER] = io_redirect_parser;
	parse->parsing[P_START][E_SEMICOLON] = separator_parser;
	parse->parsing[P_START][E_END] = end_parser;
}

void	init_string(t_parser *parse)
{
	parse->parsing[P_STRING][E_STRING] = string_parser;
	parse->parsing[P_STRING][E_QUOTE] = single_quote_parser;
	parse->parsing[P_STRING][E_GREAT] = redirect_parser;
	parse->parsing[P_STRING][E_LESS] = redirect_parser;
	parse->parsing[P_STRING][E_DGREAT] = redirect_parser;
	parse->parsing[P_STRING][E_IO_NUMBER] = io_redirect_parser;
	parse->parsing[P_STRING][E_PIPE] = flush_string;
	parse->parsing[P_STRING][E_SEMICOLON] = flush_string;
	parse->parsing[P_STRING][E_END] = flush_string;
}

void	init_single_quote(t_parser *parse)
{
	parse->parsing[P_QUOTE][E_STRING] = string_parser;
	parse->parsing[P_QUOTE][E_QUOTE] = single_quote_parser;
	parse->parsing[P_QUOTE][E_GREAT] = redirect_parser;
	parse->parsing[P_QUOTE][E_LESS] = redirect_parser;
	parse->parsing[P_QUOTE][E_DGREAT] = redirect_parser;
	parse->parsing[P_QUOTE][E_IO_NUMBER] = io_redirect_parser;
	parse->parsing[P_QUOTE][E_SEMICOLON] = flush_string;
	parse->parsing[P_QUOTE][E_END] = flush_string;
}

void	init_flush_string(t_parser *parse)
{
	parse->parsing[P_STRING_FLUSH][E_PIPE] = pipe_parser;
	parse->parsing[P_STRING_FLUSH][E_END] = end_parser;
	parse->parsing[P_STRING_FLUSH][E_SEMICOLON] = separator_parser;
}

void	init_separator(t_parser *parse)
{
	parse->parsing[P_SEPARATOR][E_STRING] = stop_parser;
	parse->parsing[P_SEPARATOR][E_QUOTE] = stop_parser;
	parse->parsing[P_SEPARATOR][E_GREAT] = stop_parser;
	parse->parsing[P_SEPARATOR][E_DGREAT] = stop_parser;
	parse->parsing[P_SEPARATOR][E_LESS] = stop_parser;
	parse->parsing[P_SEPARATOR][E_SEMICOLON] = stop_parser;
	parse->parsing[P_SEPARATOR][E_END] = end_parser;
}

void	init_pipe(t_parser *parse)
{
	parse->parsing[P_PIPE][E_STRING] = string_parser;
	parse->parsing[P_PIPE][E_QUOTE] = single_quote_parser;
	parse->parsing[P_PIPE][E_GREAT] = redirect_parser;
	parse->parsing[P_PIPE][E_LESS] = redirect_parser;
	parse->parsing[P_PIPE][E_DGREAT] = redirect_parser;
	parse->parsing[P_PIPE][E_IO_NUMBER] = io_redirect_parser;
}

void	init_suffix_redirect(t_parser *parse)
{
	parse->parsing[P_REDIRECT][E_STRING] = filename_state;
	parse->parsing[P_REDIRECT][E_QUOTE] = filename_state;
}

void	init_filename(t_parser *parse)
{
	parse->parsing[P_FILENAME][E_STRING] = flush_redirect;
	parse->parsing[P_FILENAME][E_QUOTE] = flush_redirect;
	parse->parsing[P_FILENAME][E_SEMICOLON] = flush_redirect;
	parse->parsing[P_FILENAME][E_END] = flush_redirect;
}

void	init_flush_redirect(t_parser *parse)
{
	parse->parsing[P_REDIRECT_FLUSH][E_STRING] = string_parser;
	parse->parsing[P_REDIRECT_FLUSH][E_QUOTE] = single_quote_parser;
	parse->parsing[P_REDIRECT_FLUSH][E_SEMICOLON] = flush_string;
	parse->parsing[P_REDIRECT_FLUSH][E_END] = end_parser;
}

void	init_parsing(t_parser *parse)
{
	init_start(parse);
	init_string(parse);
	init_single_quote(parse);
	init_flush_string(parse);
	init_separator(parse);
	init_suffix_redirect(parse);
	init_filename(parse);
	init_flush_redirect(parse);
	init_pipe(parse);
}
