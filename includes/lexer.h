/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 14:21:32 by ffoissey          #+#    #+#             */
/*   Updated: 2019/04/16 17:50:04 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "libft.h"
# define STATENBR 15
# define NB_OF_TOKENS 52
# define TOKEN_WITH_DATA 6
# define BUFFER 1024
# define SINGLE_SIGNS 25
# define SPECIAL_SIGNS 10
# define SIGNS (SPECIAL_SIGNS + SINGLE_SIGNS)

# define ALLCHAR "$ \\\'\"|()><;`&~{}[]*?!#=%N"
# define QUOTE_INTERUPT "\\\"`$"
# define EXP_INTERUPT " \t\'\"`"
# define DOUBLE_SIGN "&|;"

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
	IO_NUMBER,
	SIGN,
	DSIGN,
	GREATER,
	LESSER,
	SPACE,
	EXP,
	BSL,
	SQTE,
	DQTE,
	BQTE,
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
	E_NEWLINE,
	E_DAND,
	E_OR,
	E_DSEMI,
	E_DLESS,
	E_DGREAT,
	E_LESSAND,
	E_GREATAND,
	E_LESSGREAT,
	E_DLESSDASH,
	E_CLOBBER,
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
	E_IO_NUMBER,
	E_STRING,
	E_QSTRING,
	E_DEFAULT,
};

enum	e_quote
{
	QUOTE_OFF,
	QUOTE_ON,
	QUOTE_INT,
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
	t_process		process[STATENBR];
	enum e_type		duplicate[TOKEN_WITH_DATA];
	enum e_type		special_signs[SPECIAL_SIGNS];
	t_list			*tokens;
	enum e_state	state;
	enum e_quote	quote;
	enum e_type		last_machine;
};

void	start_machine(t_machine *machine);
void	end_machine(t_machine *machine);
void	out_machine(t_machine *machine);
void	space_machine(t_machine *machine);
void	letter_machine(t_machine *machine);
void	number_machine(t_machine *machine);
void	sign_machine(t_machine *machine);
void	expansion_machine(t_machine *machine);
void	backslash_machine(t_machine *machine);
void	single_quote_machine(t_machine *machine);
void	double_quote_machine(t_machine *machine);
void	double_sign_machine(t_machine *machine);
void	greater_machine(t_machine *machine);
void	lesser_machine(t_machine *machine);

void	fill_buffer_output(t_machine *machine);
t_token generate_token(t_machine *machine);

t_list		*lexer(char *input);

/*
** Temporary display functions | REMOVE BEFOR PUSH
*/

void	print_list(t_list *list);
void	del_token(void *token);

void		parser(t_list *lst);

#endif
