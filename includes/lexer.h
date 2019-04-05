/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 14:21:32 by ffoissey          #+#    #+#             */
/*   Updated: 2019/04/05 11:48:57 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "libft.h"
# define BUFFER 1024
# define OFFSET 24

# define PIPE "|"
# define QUOTE "\'"
# define DB_QUOTE "\""
# define PARENT_OPEN "("
# define PARENT_CLOSE ")"
# define SP " "
# define FORWARD ">"
# define BACKWARD "<"
# define SEMICOLON ";"
# define BACKQUOTE "`"
# define AND "&"
# define DOLLAR "$"
# define TILDE "~"
# define HOOK_OPEN "{"
# define HOOK_CLOSE "}"
# define BRACKET_OPEN "["
# define BRACKET_CLOSE "]"
# define STAR "*"
# define INTERROGATION "?"
# define EXCLAMATION "!"
# define HASH "#"
# define EQUAL "="
# define PERCENT "%"
# define BACKSLASH "\\"

# define ALLCHAR "$ \\\'\"|()><;`&~{}[]*?!#=%"

# define CASE "case"
# define DO "do"
# define DONE "done"
# define ELIF "elif"
# define ELSE "else"
# define ESAC "esac"
# define FI "fi"
# define FOR "for"
# define IF "if"
# define IN "in"
# define THEN "then"
# define UNTIL "until"
# define WHILE "while"

# define FINALCHAR " \t<>|;\'\"`()$&!?{}[]*%\\=" ///MISS OPERATORS

typedef struct s_state t_state;
typedef  void (*t_process)(t_state *);

enum	e_state
{
	START,
	LETTER,
	SIGN,
	SPACE,
	EXP,
	BSL,
	SQTE,
	OUT,
	END
};

enum	e_type
{
	E_EXP,
	E_SPACE,
	E_BACKSLASH,
	E_QUOTE,
	E_DB_QUOTE,
	E_PIPE,
	E_PARENT_OPEN,
	E_PARENT_CLOSE,
	E_FORWARD,
	E_BACKWARD,
	E_SEMICOLON,
	E_BACKQUOTE,
	E_AND,
	E_TILDE,
	E_HOOK_OPEN,
	E_HOOK_CLOSE,
	E_BRACKET_OPEN,
	E_BRACKET_CLOSE,
	E_STAR,
	E_INTERROGATION,
	E_EXCLAMATION,
	E_HASH,
	E_EQUAL,
	E_PERCENT,
	E_CASE,
	E_DO,
    E_DONE,
    E_ELIF,
    E_ELSE,
    E_ESAC,
    E_FI,
    E_FOR,
    E_IF,
    E_IN,
    E_THEN,
    E_UNTIL,
    E_WHILE,
	E_STRING,
	E_QSTRING,
};

enum	e_quote
{
	NO_QUOTE,
	SQUOTE_ON,
	DQUOTE_ON
};

typedef struct	s_token
{
	enum e_type	type;
	char		*data;
}				t_token;

struct	s_state
{
	char			*input;
	char			buffer[BUFFER];
	enum e_type		duplicate[5];
	t_list			*lst;
	enum e_quote	quote;
	enum e_state	state;
	enum e_state	last_state;
	t_process		process;
};

void	start_machine(t_state *machine);
void	end_machine(t_state *machine);
void	out_machine(t_state *machine);
void	space_machine(t_state *machine);
void	letter_machine(t_state *machine);
void	sign_machine(t_state *machine);
void	expansion_machine(t_state *machine);
void	backslash_machine(t_state *machine);
void	single_quote_machine(t_state *machine);

void	fill_buffer_output(t_state *machine);
t_token generate_token(t_state *machine);

void		parser(t_list *lst);

#endif
