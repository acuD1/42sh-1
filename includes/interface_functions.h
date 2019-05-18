/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface_functions.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <skuppers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 15:54:02 by skuppers          #+#    #+#             */
/*   Updated: 2019/05/18 13:18:30 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERFACE_FUNCTIONS_H
# define INTERFACE_FUNCTIONS_H

# include "struct.h"

uint64_t				setup_interface(t_registry *shell);
void					teardown_interface(t_registry *shell);
/*
*****************************************************
************** INIT / SETTING / FREE ****************
*****************************************************
*/

uint64_t	get_terminal_info(t_registry *shell);
uint64_t    set_terminal_mode(t_registry *shell);
uint64_t	init_termcaps(t_termcaps *termcp);

uint64_t	assign_keycodes(t_interface *itf);
uint64_t    link_keys_functions(int8_t (*tc_call[AK_AMOUNT])(t_registry *shell));
uint64_t    set_interface_internals(t_registry *shell);
uint64_t    init_line(t_interface *interface);

uint64_t    init_window(t_registry *shell);
uint64_t    init_cursor(t_interface *interface);
uint64_t    init_prompt(t_interface *interface);


t_vector	*prompt(t_registry *shell, char *p_state);
t_vector	*sub_prompt(t_registry *shell, char *s, char *m);

void		update_window(t_registry *shell);

void		handle_input_key(t_registry *shell, char c[READ_SIZE ]);

int			ft_putc(const int c);
uint8_t		is_eof(const char *buffer);


void		set_redraw_flags(t_interface *itf, uint32_t rd_flag);
void		set_redraw_bounds(t_interface *itf, uint64_t s, uint64_t e);
void		set_cursor_pos(t_interface *itf, uint64_t index);

void		redraw(t_registry *shell);

void		print_char(t_interface *itf, char c);
void		print_loop(t_interface *itf, char *str);
void		print_prompt(t_registry *shell, char *state);

void		define_interface_signal_behavior(t_registry *shell);
short		restore_term_behavior(t_registry *shell);

t_coord		*index_to_coord(t_window *window, uint64_t indx);
uint64_t	get_prompt_length(t_prompt *prompt);

/*
*****************************************************
********** UNIT TESTING / BUFFER / UTILS ************
*****************************************************
*/



uint64_t	compute_mask(char c[READ_SIZE]);

void		link_actions_to_keys(int8_t (*tc_call[AK_AMOUNT])
				(struct s_registry *shell));

/*
*****************************************************
********************* DISPLAY ***********************
*****************************************************
*/

void		interface_resize_handler(const int signo);


/*
*****************************************************
********************* PROMPT ************************
*****************************************************
*/


/*
*****************************************************
******************** ACTION KEYS ********************
*****************************************************
*/

int8_t		tc_ak_ctrl_d(t_registry *shell);
int8_t		tc_ak_next_word(t_registry *shell);
int8_t		tc_ak_prev_word(t_registry *shell);
int8_t		tc_ak_cut_before_cursor(t_registry *shell);
int8_t		tc_ak_cut_after_cursor(t_registry *shell);
int8_t		tc_ak_copy_before_cursor(t_registry *shell);
int8_t		tc_ak_copy_after_cursor(t_registry *shell);
int8_t		tc_ak_cut_line(t_registry *shell);
int8_t		tc_ak_copy_line(t_registry *shell);
int8_t		tc_ak_paste_clipboard(t_registry *shell);
int8_t		tc_ak_clear_screen(t_registry *shell);
int8_t		tc_ak_home(t_registry *shell);
int8_t		tc_ak_end(t_registry *shell);
int8_t		tc_ak_delete(t_registry *shell);
int8_t		tc_ak_backspace(t_registry *shell);
int8_t		tc_ak_arrow_up(t_registry *shell);
int8_t		tc_ak_arrow_down(t_registry *shell);
int8_t		tc_ak_arrow_left(t_registry *shell);
int8_t		tc_ak_arrow_right(t_registry *shell);
int8_t		tc_ak_hightab(t_registry *shell);
int8_t		tc_ak_ctrl_down(t_registry *shell);
int8_t		tc_ak_ctrl_up(t_registry *shell);

#endif
