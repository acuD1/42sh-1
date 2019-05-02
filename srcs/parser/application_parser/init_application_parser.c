/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_application_parser.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 21:57:35 by cempassi          #+#    #+#             */
/*   Updated: 2019/05/02 02:22:55 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	bzero_parsing(t_pstate parsing)
{
	int		index;
	int		state;

	index = 0;
	while (index < PARSE_STATES)
	{
		state = 0;
		while (state < NB_OF_TOKENS)
			parsing[index][state++] = error_parser;
		++index;
	}
}

static void	init_start(t_pstate parsing)
{
	parsing[P_START][E_STRING] = string_parser;
	parsing[P_START][E_SPSTRING] = special_string_parser;
	parsing[P_START][E_GREAT] = redirect_parser;
	parsing[P_START][E_GREATAND] = redirect_parser;
	parsing[P_START][E_LESS] = redirect_parser;
	parsing[P_START][E_LESSAND] = redirect_parser;
	parsing[P_START][E_DGREAT] = redirect_parser;
	parsing[P_START][E_ANDDGREAT] = redirect_parser;
	parsing[P_START][E_IO_NUMBER] = io_parser;
	parsing[P_START][E_SEMICOLON] = separator_parser;
	parsing[P_START][E_END] = end_parser;
}

static void	init_string(t_pstate parsing)
{
	parsing[P_STRING][E_STRING] = string_parser;
	parsing[P_STRING][E_SPSTRING] = special_string_parser;
	parsing[P_STRING][E_GREAT] = redirect_parser;
	parsing[P_STRING][E_GREATAND] = redirect_parser;
	parsing[P_STRING][E_LESS] = redirect_parser;
	parsing[P_STRING][E_LESSAND] = redirect_parser;
	parsing[P_STRING][E_DGREAT] = redirect_parser;
	parsing[P_STRING][E_ANDDGREAT] = redirect_parser;
	parsing[P_STRING][E_IO_NUMBER] = io_parser;
	parsing[P_STRING][E_PIPE] = flush_string;
	parsing[P_STRING][E_SEMICOLON] = flush_string;
	parsing[P_STRING][E_END] = flush_string;
}

static void	init_special_string(t_pstate parsing)
{
	parsing[P_SPSTRING][E_STRING] = string_parser;
	parsing[P_SPSTRING][E_SPSTRING] = special_string_parser;
	parsing[P_SPSTRING][E_GREAT] = redirect_parser;
	parsing[P_SPSTRING][E_GREATAND] = redirect_parser;
	parsing[P_SPSTRING][E_LESS] = redirect_parser;
	parsing[P_SPSTRING][E_LESSAND] = redirect_parser;
	parsing[P_SPSTRING][E_DGREAT] = redirect_parser;
	parsing[P_SPSTRING][E_ANDDGREAT] = redirect_parser;
	parsing[P_SPSTRING][E_IO_NUMBER] = io_parser;
	parsing[P_SPSTRING][E_PIPE] = flush_string;
	parsing[P_SPSTRING][E_SEMICOLON] = flush_string;
	parsing[P_SPSTRING][E_END] = flush_string;
}

static void	init_flush_string(t_pstate parsing)
{
	parsing[P_STRING_FLUSH][E_PIPE] = pipe_parser;
	parsing[P_STRING_FLUSH][E_END] = end_parser;
	parsing[P_STRING_FLUSH][E_SEMICOLON] = separator_parser;
}

static void	init_separator(t_pstate parsing)
{
	parsing[P_SEPARATOR][E_STRING] = stop_parser;
	parsing[P_SEPARATOR][E_SPSTRING] = stop_parser;
	parsing[P_SEPARATOR][E_GREAT] = stop_parser;
	parsing[P_SEPARATOR][E_GREATAND] = stop_parser;
	parsing[P_SEPARATOR][E_LESS] = stop_parser;
	parsing[P_SEPARATOR][E_LESSAND] = stop_parser;
	parsing[P_SEPARATOR][E_DGREAT] = stop_parser;
	parsing[P_SEPARATOR][E_ANDDGREAT] = stop_parser;
	parsing[P_SEPARATOR][E_SEMICOLON] = stop_parser;
	parsing[P_SEPARATOR][E_END] = end_parser;
}

static void	init_pipe(t_pstate parsing)
{
	parsing[P_PIPE][E_STRING] = string_parser;
	parsing[P_PIPE][E_SPSTRING] = special_string_parser;
	parsing[P_PIPE][E_GREAT] = redirect_parser;
	parsing[P_PIPE][E_GREATAND] = redirect_parser;
	parsing[P_PIPE][E_LESS] = redirect_parser;
	parsing[P_PIPE][E_LESSAND] = redirect_parser;
	parsing[P_PIPE][E_DGREAT] = redirect_parser;
	parsing[P_PIPE][E_ANDDGREAT] = redirect_parser;
	parsing[P_PIPE][E_IO_NUMBER] = io_parser;
}

static void	init_suffix_redirect(t_pstate parsing)
{
	parsing[P_REDIRECT][E_STRING] = filename_state;
}

static void	init_filename(t_pstate parsing)
{
	parsing[P_FILENAME][E_STRING] = flush_redirect;
	parsing[P_FILENAME][E_SPSTRING] = flush_redirect;
	parsing[P_FILENAME][E_GREAT] = flush_redirect;
	parsing[P_FILENAME][E_GREATAND] = flush_redirect;
	parsing[P_FILENAME][E_LESS] = flush_redirect;
	parsing[P_FILENAME][E_LESSAND] = flush_redirect;
	parsing[P_FILENAME][E_DGREAT] = flush_redirect;
	parsing[P_FILENAME][E_ANDDGREAT] = flush_redirect;
	parsing[P_FILENAME][E_PIPE] = flush_redirect;
	parsing[P_FILENAME][E_SEMICOLON] = flush_redirect;
	parsing[P_FILENAME][E_END] = flush_redirect;
}

static void	init_flush_redirect(t_pstate parsing)
{
	parsing[P_REDIRECT_FLUSH][E_STRING] = string_parser;
	parsing[P_REDIRECT_FLUSH][E_SPSTRING] = special_string_parser;
	parsing[P_REDIRECT_FLUSH][E_PIPE] = flush_string;
	parsing[P_REDIRECT_FLUSH][E_SEMICOLON] = flush_string;
	parsing[P_REDIRECT_FLUSH][E_END] = flush_string;
}

void		init_parsing(t_pstate parsing)
{
	bzero_parsing(parsing);
	init_start(parsing);
	init_string(parsing);
	init_special_string(parsing);
	init_flush_string(parsing);
	init_separator(parsing);
	init_suffix_redirect(parsing);
	init_filename(parsing);
	init_flush_redirect(parsing);
	init_pipe(parsing);
}
