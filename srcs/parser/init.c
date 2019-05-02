/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 21:57:35 by cempassi          #+#    #+#             */
/*   Updated: 2019/05/02 23:10:33 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	bzero_parsing(t_pstate parsing)
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

void	init_start(t_pstate parsing)
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

void	init_string(t_pstate parsing)
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

void	init_special_string(t_pstate parsing)
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

void	init_flush_string(t_pstate parsing)
{
	parsing[P_STRING_FLUSH][E_PIPE] = pipe_parser;
	parsing[P_STRING_FLUSH][E_END] = end_parser;
	parsing[P_STRING_FLUSH][E_SEMICOLON] = separator_parser;
}

void	init_separator(t_pstate parsing)
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

void	init_pipe(t_pstate parsing)
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

void	init_redirect(t_pstate parsing)
{
	parsing[P_REDIRECT][E_STRING] = filename_parser;
	parsing[P_REDIRECT][E_SPSTRING] = special_filename_parser;
}

void	init_filename(t_pstate parsing)
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

void	init_special_filename(t_pstate parsing)
{
	parsing[P_SPFILENAME][E_STRING] = flush_redirect;
	parsing[P_SPFILENAME][E_SPSTRING] = flush_redirect;
	parsing[P_SPFILENAME][E_GREAT] = flush_redirect;
	parsing[P_SPFILENAME][E_GREATAND] = flush_redirect;
	parsing[P_SPFILENAME][E_LESS] = flush_redirect;
	parsing[P_SPFILENAME][E_LESSAND] = flush_redirect;
	parsing[P_SPFILENAME][E_DGREAT] = flush_redirect;
	parsing[P_SPFILENAME][E_ANDDGREAT] = flush_redirect;
	parsing[P_SPFILENAME][E_PIPE] = flush_redirect;
	parsing[P_SPFILENAME][E_SEMICOLON] = flush_redirect;
	parsing[P_SPFILENAME][E_END] = flush_redirect;
}

void	init_flush_redirect(t_pstate parsing)
{
	parsing[P_REDIRECT_FLUSH][E_STRING] = string_parser;
	parsing[P_REDIRECT_FLUSH][E_SPSTRING] = special_string_parser;
	parsing[P_REDIRECT_FLUSH][E_PIPE] = flush_string;
	parsing[P_REDIRECT_FLUSH][E_SEMICOLON] = flush_string;
	parsing[P_REDIRECT_FLUSH][E_END] = flush_string;
}

void	init_io(t_pstate parsing)
{
	parsing[P_IO][E_GREAT] = io_redirect_parser;
	parsing[P_IO][E_DGREAT] = io_redirect_parser;
	parsing[P_IO][E_LESS] = io_redirect_parser;
	parsing[P_IO][E_GREATAND] = io_redirect_and_parser;
	parsing[P_IO][E_LESSAND] = io_redirect_and_parser;
}

void	init_io_redirect(t_pstate parsing)
{
	parsing[P_IO_REDIRECT][E_STRING] = io_filename_parser;
	parsing[P_IO_REDIRECT][E_SPSTRING] = io_filename_parser;
}

void	init_io_filename_and(t_pstate parsing)
{
	parsing[P_IO_REDIRECT][E_STRING] = io_dup_move_parser;
	parsing[P_IO_REDIRECT][E_SPSTRING] = io_dup_move_parser;

}

void	init_parsing(t_pstate parsing)
{
	bzero_parsing(parsing);
	init_start(parsing);
	init_string(parsing);
	init_special_string(parsing);
	init_flush_string(parsing);
	init_separator(parsing);
	init_redirect(parsing);
	init_filename(parsing);
	init_special_filename(parsing);
	init_flush_redirect(parsing);
	init_pipe(parsing);
}
