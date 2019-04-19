/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 21:57:35 by cempassi          #+#    #+#             */
/*   Updated: 2019/04/19 14:44:06 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	bzero_parsing(t_parser *parse)
{
	int		index;
	int		state;

	index = 0;
	while (index < PARSE_STATES)
	{
		state = 0;
		while (state < NB_OF_TOKENS)
			parse->parsing[index][state++] = parse_error;
		++index;
	}
}

void	init_start(t_parser *parse)
{
	parse->parsing[P_START][E_STRING] = string_parser;
	parse->parsing[P_START][E_QUOTE] = single_quote_parser;
}

void	init_flush_string(t_parser *parse)
{
	parse->parsing[P_STRING_FLUSH][E_END] = end_parser;
	parse->parsing[P_STRING_FLUSH][E_SEMICOLON] = separator_parser;
}

void	init_separator(t_parser *parse)
{
	parse->parsing[P_SEPARATOR][E_END] = end_parser;
	parse->parsing[P_SEPARATOR][E_STRING] = stop_parser;
	parse->parsing[P_SEPARATOR][E_QUOTE] = stop_parser;
}

void	init_single_quote(t_parser *parse)
{
	parse->parsing[P_QUOTE][E_QUOTE] = single_quote_parser;
	parse->parsing[P_QUOTE][E_STRING] = string_parser;
	parse->parsing[P_QUOTE][E_END] = flush_string;
	parse->parsing[P_QUOTE][E_SEMICOLON] = flush_string;
}

void	init_string(t_parser *parse)
{
	parse->parsing[P_STRING][E_STRING] = string_parser;
	parse->parsing[P_STRING][E_END] = flush_string;
	parse->parsing[P_STRING][E_SEMICOLON] = flush_string;
	parse->parsing[P_STRING][E_QUOTE] = single_quote_parser;
}

void	init_parsing(t_parser *parse)
{
	bzero_parsing(parse);
	init_start(parse);
	init_string(parse);
	init_flush_string(parse);
	init_separator(parse);
}
