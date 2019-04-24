/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 13:39:31 by cempassi          #+#    #+#             */
/*   Updated: 2019/04/24 16:42:52 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "lexer.h"
# define TRUE 1
# define FALSE 0
# define PARSE_STATES 2
# define WORD E_STRING, E_EXP, E_QUOTE, E_DB_QUOTE, E_BACKSLASH
# define IO E_IO_NUMBER
# define PIPELINE E_PIPE
# define BASE_REDIRECT E_GREAT, E_LESS, E_DLESS, E_DGREAT
# define AND_REDIRECT E_GREATAND, E_LESSAND
# define REDIRECT AND_REDIRECT, BASE_REDIRECT
# define END_CMD E_SEMICOLON, E_END
# define ALL WORD, BASE_REDIRECT, IO
# define ALL_END ALL, END_CMD
# define E_START E_DEFAULT

typedef struct	s_exec
{
	int		ac;
	char	**av;
	char	**env;
	int		fdin;
	int		fdout;
	int		fderror;
	gid_t	gid;
}				t_exec;

enum	e_event
{
	NO_EVENT,
	START_GRAPH,
	END_GRAPH,
	RECALL,
	BACK,
	ERROR_GRAPH
};

enum	e_parser_state
{
	P_STRING,
	P_START,
	P_END,
};

typedef struct s_graph	t_graph;
typedef struct s_parser	t_parser;
typedef void (*t_parsing)(t_parser *);

struct s_parser
{
	t_list				*token_list;
	enum e_type			state;
	t_exec				current_exec;
	t_list				*parse_output;
	t_list				*av;
	t_token				*token;
	t_parsing			parsing[NB_OF_TOKENS];
};

void	parser_start(t_parser *machine);

struct s_graph
{
	enum e_type		*good_type;
	int				nb_of_good_type;
};

/*
************************
****  parser_debug  ****
************************
*/

void		print_token_debug(t_token *token);
void		print_arrow_debug(int which);
void		print_error_debug(enum e_type type, int which);
void		print_result_debug(int which);

/*
************************
**  set_parser_token  **
************************
*/

void		set_start_token(t_graph *tab);
void		set_word_token(t_graph *tab);
void		set_redirect_token(t_graph *tab);
void		set_assign_token(t_graph *tab);
void		set_semicolon_token(t_graph *tab);
void		set_pipe_token(t_graph *tab);
void		set_ionumber_token(t_graph *tab);

/*
************************
**   generate_graph   **
************************
*/

t_graph		*generate_graph(void);

#endif
