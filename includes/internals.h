/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   internals.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 16:41:15 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/02 18:31:30 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERNALS_H
# define INTERNALS_H

#define INT_DBG_FD_NAME "DEBUG_FD"
#define INT_DBG_FILE ".42sh.log"

#define INT_ROWS_NAME "ROWS"
#define INT_ROWS "0"
#define INT_COLS_NAME "COLS"
#define INT_COLS "0"

#define INT_READ_SZ_NAME "READSZ"
#define INT_READ_SZ "16"
#define INT_CLIPBOARD_SZ_NAME "CLIPBOARDSZ"
#define INT_CLIPBOARD_SZ "32"

#define INT_PS1_NAME "PS1"
#define INT_PS1 "[21sh] -> "
#define INT_PS1_L_NAME "PS1SZ"
#define INT_PS1_LENGTH "10"

#define INT_PS2_NAME "PS2"
#define INT_PS2 "quote> "
#define INT_PS2_L_NAME "PS2SZ"
#define INT_PS2_LENGTH "7"

#define INT_IFS_NAME "IFS"
#define INT_IFS "10"
#define INT_ESCAPE_NAME "ESC"
#define INT_ESCAPE "\\"

#define INT_MAGIC_NUMBER "4242"

#endif
