/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   internals.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 16:41:15 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/11 18:59:53 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERNALS_H
# define INTERNALS_H

/*
**	INTERFACE RELATED
*/
#define IFS_CHAR 10
#define READ_SIZE 8
#define CLIPBOARD_SZ 32

#define INT_TERM "TERM"
#define INT_TERM_DFLT_VALUE "xterm-256color"

#define INT_DBG_FD "DEBUG_FD"
#define INT_DBG_FILE ".42sh.log"

#define INT_ROWS "ROWS"
#define INT_COLS "COLS"



#define INT_PS1 "PS1"
#define INT_PS1_VALUE "[21sh] -> "

#define INT_PS2 "PS2"
#define INT_PS2_VALUE "quote> "

#define INT_PS3 "PS3"
#define INT_PS3_VALUE "script>"

#define INT_PS4 "PS4"
#define INT_PS4_VALUE "heredoc>"


#define INT_ESCAPE_SEQ "ESC"
#define INT_ESCAPE_SEQ_VALUE "\\"

#define INT_MAGIC_NUMBER "4242"

/*
**	LEXER, etc...
*/


#endif
