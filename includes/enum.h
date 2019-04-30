/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enum.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 15:25:34 by ffoissey          #+#    #+#             */
/*   Updated: 2019/04/30 20:45:00 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENUM_H
# define ENUM_H

/*
*****************************************************
********************** BUILTIN **********************
*****************************************************
*/

enum	e_state_option
{
		E_START_OPTION,
		E_OPTION,
		E_END_OPTION,
		E_NO_OPTION
};

/*
*****************************************************
*********************** LEXER ***********************
*****************************************************
*/

enum	e_lexer_state
{
		START,
		LETTER,
		IO_NUMBER,
		SIGN,
		DSIGN,
		GREATER,
		LESSER,
		GREATAND,
		LESSAND,
		TILDE,
		EXP,
		BSL,
		SQTE,
		DQTE,
		BQTE,
		AND,
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
		E_QSTRING,
		E_ASSIGN,
		E_END,
		E_QEXP,
		E_QTILDE,
		E_DGREATAND,
		E_ANDGREAT,
		E_ANDLESS,
		E_DEFAULT,
		E_ERROR
};

enum	e_quote
{
		QUOTE_OFF,
		QUOTE_ON,
		QUOTE_INT,
		QUOTE_SP,
		QUOTE_SP_INT
};

/*
*****************************************************
********************** PARSER ***********************
*****************************************************
*/

enum	e_parser_state
{
		P_START,
		P_END,
		P_STOP,
		P_ERROR,
		P_STRING,
		P_QUOTE,
		P_EXP,
		P_DB_QUOTE,
		P_DB_QUOTE_CONCAT,
		P_STRING_FLUSH,
		P_SEPARATOR,
		P_REDIRECT,
		P_REDIRECT_FLUSH,
		P_FILENAME,
		P_IO,
		P_IO_REDIRECT,
		P_IO_FILENAME,
		P_IO_FLUSH,
		P_PIPE,
		P_HEREDOC,
};

enum	e_event
{
		NO_EVENT,
		START_GRAPH,
		END_GRAPH,
		RECALL,
		BACK,
		ERROR_GRAPH
};

/*
*****************************************************
**************** INTERFACE_FUNCTIONS ****************
*****************************************************
*/

enum	action_keys
{
		AK_ARROW_RIGHT,
		AK_ARROW_LEFT,
		AK_ARROW_UP,
		AK_ARROW_DOWN,
		AK_HOME,
		AK_END,
		AK_BACKSPACE,
		AK_DELETE,
		AK_CTRL_A,
		AK_CTRL_D,
		AK_CTRL_E,
		AK_CTRL_L,
		AK_CTRL_X,
		AK_CTRL_B,
		AK_CTRL_P,
		AK_CTRL_LB,
		AK_CTRL_RB,
		AK_CTRL_F,
		AK_CTRL_R,
		AK_CTRL_LEFT,
		AK_CTRL_RIGHT,
		AK_TABULATION,
		AK_CTRL_DOWN,
		AK_CTRL_UP
};

#endif
