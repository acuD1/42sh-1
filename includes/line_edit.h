/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_edit.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 09:33:05 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/15 11:49:52 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINE_EDIT_H
# define LINE_EDIT_H

#include <termcap.h>
#include <term.h>
#include <termios.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>

#include "21sh.h"
#include "libft.h"

# define AK_AMOUNT 24
#define AK_ARROW_UP_MASK	0x1b5b410000000000
#define AK_ARROW_DOWN_MASK 	0x1b5b420000000000
#define AK_ARROW_RIGHT_MASK 0x1b5b430000000000
#define AK_ARROW_LEFT_MASK 	0x1b5b440000000000
#define AK_HOME_MASK 		0x1b5b480000000000
#define AK_END_MASK 		0x1b5b460000000000
#define AK_CTRL_A_MASK 		0x100000000000000
#define AK_CTRL_E_MASK	    0x500000000000000
#define AK_DELETE_MASK	    0x1b5b337e00000000
#define AK_BACKSPACE_MASK 	0x7f00000000000000
#define AK_CTRL_D_MASK 		0x400000000000000
#define AK_CTRL_L_MASK		0xc00000000000000
#define AK_CTRL_X_MASK		0x1800000000000000
#define AK_CTRL_B_MASK		0x2000000000000000
#define AK_CTRL_P_MASK		0x1000000000000000
#define AK_CTRL_LB_MASK		0x1b00000000000000
#define AK_CTRL_RB_MASK		0x1d00000000000000
#define AK_CTRL_F_MASK		0x600000000000000
#define AK_CTRL_R_MASK		0x1200000000000000
#define AK_CTRL_UP_MASK		0x1b5b313b35410000
#define AK_CTRL_DOWN_MASK	0x1b5b313b35420000
#define AK_CTRL_RIGHT_MASK	0x1b5b313b35430000
#define AK_CTRL_LEFT_MASK	0x1b5b313b35440000
#define AK_TAB_MASK			0x900000000000000

enum action_keys {
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
	AK_CTRL_UP,
};


typedef struct				s_termcaps
{
	char					*clear;
	char					*cs_down;
	char					*cs_right;
	char					*cs_left;
	char					*cs_up;
}							t_termcaps;

typedef struct				s_cursor
 {
	uint32_t				index;
	uint32_t				x;
	uint32_t				y;
}							t_cursor;

typedef struct				s_window
{
	uint32_t				rows;
	uint32_t				cols;
	uint32_t				max_chars;
}							t_window;

typedef struct				s_interface
{
	t_vector				*line;
	t_vector				*clip;
	t_cursor				*cursor;
	t_window				*window;
	t_termcaps				*termcaps;

	char					*state;
	unsigned long			ak_masks[AK_AMOUNT];

	int8_t					(*tc_call[AK_AMOUNT])(struct s_registry *shell);
}							t_interface;

#endif
