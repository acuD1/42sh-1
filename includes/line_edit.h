/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_edit.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 09:33:05 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/09 21:24:30 by cempassi         ###   ########.fr       */
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

# define READ_SIZE 8

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


typedef struct	s_termcaps
{
	char					*clear;
	char					*begin_insertion;
	char					*end_insertion;
	char					*cs_down;
	char					*cs_right;
	char					*cs_left;
	char					*cs_up;
}							t_termcaps;

typedef struct				s_winsize
{
	unsigned int			x;
	unsigned int			y;
	unsigned int			rows;
	unsigned int			cols;
	int						max_line_len;
	size_t					cursor;
}							t_winsize;

typedef struct				s_interface_registry
{
	t_registry				*sh_reg;
	unsigned long			ak_masks[AK_AMOUNT];

	t_vector				*clip;
	t_vector				*line;
	t_termcaps				*termcaps;
	t_winsize				*window;

	struct termios			*orig_term;
	struct termios			*new_term;

	char					*interface_state;

	int					(*tc_call[AK_AMOUNT])(struct s_interface_registry *itf);
}							t_interface_registry;



//Refacto functions
int	validate_interface_content(t_interface_registry *itf);
void	forge_vector(t_vector *dest, t_vector *source);


//char						*get_itf_intern_var(t_interface_registry *itf_reg, char *name);
/*  CHANGE THIS FO UNIT TEST */
void handle_printable_char(char c, t_interface_registry *itf_reg);
int	fill_interface_data(t_registry *sh, t_interface_registry *itf_reg);
int	prepare_clipboard(t_vector *clipboard, t_vector *vct);
void move_buffer(char *dest, t_vector *source);
void copy_buffer_part(t_vector *clipboard, t_vector *source, t_winsize *ws, int direction);

extern t_interface_registry	*g_interface_registry_pointer;

t_termcaps					*init_termcap_calls(t_registry *reg);
t_interface_registry		*init_line_edition(t_registry *reg);
t_vector					*allocate_clipboard(t_registry *sh_reg);
t_winsize 					*init_win_struct(t_registry *reg, t_interface_registry *itf_reg);

void						define_interface_default_signals(t_registry *sh_reg);
void						define_interface_signal_behavior(t_interface_registry *itf_reg, t_registry *shell_reg);

int							invoke_ps2_prompt(t_registry *sh, t_interface_registry *itf);
void						launch_shell_prompt(t_registry *reg, t_interface_registry *itf_registry);
char						*prompt(t_registry *shell_reg, t_interface_registry *itf_reg);

int							setup_keycodes(t_interface_registry *itf_reg);
void						init_ak_keycodes(t_interface_registry *itf_reg);
int							link_actions_to_keys(t_interface_registry *itf_reg);
void						init_termcap_actions(int (*tc_call[AK_AMOUNT])(t_interface_registry *itf_registry));

void						handle_input_key(char c[], t_interface_registry *itf_reg);
char						set_quote(char c);
void						validate_input_quoting(t_registry *sh_reg, t_interface_registry *itf_reg);

void						print_char(char c, t_interface_registry *itf_reg);
int							clean_screen(t_interface_registry *itf_reg);
void						print_words(char *str, t_interface_registry *itf_reg);
void						redraw_prompt(int signo);
int							replace_input_line(char *string, t_interface_registry *itf_reg);
int							redraw_input_line(t_interface_registry *itf_reg);
void						redraw_after_cursor(t_interface_registry *itf_reg);

void						free_interface_registry(t_interface_registry *itf_reg);
void						cleanup_interface_registry(t_interface_registry *itf_reg);
void						restore_original_term_behavior(t_registry *sh_reg, t_interface_registry *itg_re);

void						prompt_read_failed(t_registry *reg, t_vector *vect);
int							get_next_char(char *str, int index, char direction);
void						shift_content_right_once(t_vector *vect, unsigned int cursor);
void						shift_content_left_once(t_vector *vect, unsigned int cursor);
int							ft_putc(int c);

int							tc_ak_ctrl_d(t_interface_registry *itf);
int							tc_ak_next_word(t_interface_registry *itf);
int							tc_ak_prev_word(t_interface_registry *itf);
int							tc_ak_cut_before_cursor(t_interface_registry *itf);
int							tc_ak_cut_after_cursor(t_interface_registry *itf);
int							tc_ak_copy_before_cursor(t_interface_registry *itf);
int							tc_ak_copy_after_cursor(t_interface_registry *itf);
int							tc_ak_cut_line(t_interface_registry *itf);
int							tc_ak_copy_line(t_interface_registry *itf);
int							tc_ak_paste_clipboard(t_interface_registry *itf);
int							tc_ak_clear_screen(t_interface_registry *itf);
int							tc_ak_home(t_interface_registry *itf);
int							tc_ak_end(t_interface_registry *itf);
int							tc_ak_delete(t_interface_registry *itf);
int							tc_ak_backspace(t_interface_registry *itf);
int							tc_ak_arrow_up(t_interface_registry *itf);
int							tc_ak_arrow_down(t_interface_registry *itf);
int							tc_ak_arrow_left(t_interface_registry *itf);
int							tc_ak_arrow_right(t_interface_registry *itf);
int							tc_ak_hightab(t_interface_registry *itf);
int							tc_ak_ctrl_down(t_interface_registry *itf);
int							tc_ak_ctrl_up(t_interface_registry *itf_registry);
#endif
