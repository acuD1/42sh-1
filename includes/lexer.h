/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 14:21:32 by ffoissey          #+#    #+#             */
/*   Updated: 2019/04/20 00:52:43 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

#include "registry.h"
# define STATENBR 15
# define TOKEN_WITH_DATA 7
# define NB_OF_TOKENS 54
# define BUFFER 1024
# define SINGLE_SIGNS 23
# define SPECIAL_SIGNS 12
# define SIGNS (SPECIAL_SIGNS + SINGLE_SIGNS)

# define ALLCHAR "$\\\'\"|()><;`&~{}[]*?!#%N"
# define SIGN_DETECT " \t<>|;\'\"$&\\"
# define LETTER_TO_QUOTE "\"\'"
# define LETTER_INTERUPT " \t<>|;\'\"$&\\"
///// 42sh
///// # define LETTER_INTERUPT " \t<>|;\'\"`()$&!?{}[]*%\\"
///// # define SIGN_DETECT " \t<>|;\'\"`()$&!?{}[]*%\\="
/////
# define QUOTE_INTERUPT "\\\"`$"
# define EXP_INTERUPT " \t\'\"`"
# define DOUBLE_SIGN "&|;=!"

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

typedef struct s_lexer t_lexer;
typedef  void (*t_lexing)(t_lexer *);
typedef enum e_type t_type;

enum	e_lexer_state
{
	START,
	LETTER,
	IO_NUMBER,
	SIGN,
	DSIGN,
	GREATER,
	LESSER,
	EXP,
	BSL,
	SQTE,
	DQTE,
	BQTE,
	OUT,
	END,
	FINISH
};

enum	e_type
{
	E_EXP,
	E_BACKSLASH,
	E_QUOTE,
	E_DB_QUOTE,
	E_PIPE,
	E_PARENT_OPEN,
	E_PARENT_CLOSE,
	E_GREAT,
	E_LESS,
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
	E_DEQ,
	E_NOTEQ,
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
	E_ASSIGN,
	E_END,
	E_DEFAULT,
	E_ERROR,
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

struct	s_lexer
{
	char				*input;
	char				buffer[BUFFER];
	t_lexing			process[STATENBR];
	enum e_type			duplicate[TOKEN_WITH_DATA];
	enum e_type			special_signs[SPECIAL_SIGNS];
	t_list				*tokens;
	enum e_lexer_state	state;
	enum e_quote		quote;
	enum e_type			last_lexer;
};

void	start_lexer(t_lexer *machine);
void	end_machine(t_lexer *machine);
void	out_lexer(t_lexer *machine);
void	letter_machine(t_lexer *machine);
void	number_machine(t_lexer *machine);
void	sign_machine(t_lexer *machine);
void	expansion_machine(t_lexer *machine);
void	backslash_machine(t_lexer *machine);
void	single_quote_machine(t_lexer *machine);
void	double_quote_machine(t_lexer *machine);
void	double_sign_machine(t_lexer *machine);
void	greater_machine(t_lexer *machine);
void	lesser_machine(t_lexer *machine);

void	fill_buffer_output(t_lexer *machine);
t_token generate_token(t_lexer *machine);

t_list		*lexer(char *input);

/*
** Temporary display functions | REMOVE BEFOR PUSH
*/

void	print_list(t_list *list);
void	del_token(void *token);

void		parser(t_list *lst);
t_list		*lexer_parser(t_registry *shell, char *input);

#endif
