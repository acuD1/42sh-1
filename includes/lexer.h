/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 14:21:32 by ffoissey          #+#    #+#             */
/*   Updated: 2019/04/03 20:02:34 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "libft.h"
# define STATENBR 10
# define TOKEN_WITH_DATA 4
# define BUFFER 1024
# define SINGLE_SIGNS 24
# define DOUBLE_SIGNS 1
# define SIGNS DOUBLE_SIGNS + SINGLE_SIGNS

# define ALLCHAR "$ \\\'\"|()><;`&~{}[]*?!#=%"

# define DAND "&&"
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

typedef struct s_machine t_machine;
typedef  void (*t_process)(t_machine *);

enum	e_state
{
	START,
	LETTER,
	SAND,
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
	E_DAND,
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

typedef struct	s_state
{
	enum e_state state;
	t_process	process;

}				t_state;

struct	s_machine
{
	char			*input;
	char			buffer[BUFFER];
	t_state			states[STATENBR];
	enum e_type		duplicate[TOKEN_WITH_DATA + 1];
	t_list			*tokens;
	t_state			current_state;
	enum e_quote	quote;
	enum e_state	state;
	enum e_state	last_machine;
	t_process		process;
};

void	start_machine(t_machine *machine);
void	end_machine(t_machine *machine);
void	out_machine(t_machine *machine);
void	space_machine(t_machine *machine);
void	letter_machine(t_machine *machine);
void	sign_machine(t_machine *machine);
void	expansion_machine(t_machine *machine);
void	backslash_machine(t_machine *machine);
void	single_quote_machine(t_machine *machine);
void	and_machine(t_machine *machine);

void	fill_buffer_output(t_machine *machine);
t_token generate_token(t_machine *machine);

#endif
