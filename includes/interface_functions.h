/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface_functions.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 15:54:02 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/27 16:14:38 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERFACE_FUNCTIONS_H
# define INTERFACE_FUNCTIONS_H

# include "21sh.h"
# include "history.h"
# include <termcap.h>
# include <termios.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/ioctl.h>

/*
*****************************************************
******************* UNIT TESTING ********************
*****************************************************
*/

int8_t						fill_interface_data(t_registry *shell,
								t_interface *itf);

void						move_buffer(char *dest, t_vector *source);
void						copy_buffer_part(t_interface *itf, int8_t before);
int							insert_clipboard(t_registry *shell);
uint8_t 					is_too_long(t_vector *a, t_vector *b, uint32_t max);
uint8_t						is_only_whitespaces(char *buffer);
unit8_t						init_termcap_calls(t_termcaps *termcp);
uint8_t						load_interface(t_registry *shell, t_interface *itf);

t_vector					*allocate_clipboard(t_registry *shell);
short						set_term_behavior(t_registry *shell);
short						restore_term_behavior(t_registry *shell);

int8_t	 					init_window(t_registry *shell, t_interface *itf);
int8_t						init_cursor(t_cursor *cursor);

void						define_interface_default_signals(t_registry *shell);
void						define_interface_signal_behavior(t_registry *shell);

int8_t						invoke_sub_prompt(t_registry *shell, char **line,
								char *prompt_state);
void						launch_shell_prompt(t_registry *shell,
								t_interface *itf);
char						*prompt(t_registry *shell, t_interface *itf);

void						setup_keycodes(t_interface *itf);
void						init_ak_keycodes(t_interface *itf);
void						link_actions_to_keys(t_registry *shell);
void						init_termcap_actions(int8_t (*tc_call[AK_AMOUNT])
								(struct s_registry *shell));
void						handle_input_key(t_registry *shell , char c[]);
char						set_quote(char c);
void						validate_input_quoting(t_registry *shell,
								t_interface *itf);
void						print_char(t_interface *itf, char c);
void						print_words(t_interface *itf, char *str);
void						redraw_prompt(int signo);
uint32_t					clean_screen(t_registry *shell);
uint32_t					replace_input_line(t_registry *shell, char *string);
uint32_t					redraw_input_line(t_registry *shell);
uint32_t					redraw_after_cursor(t_registry *shell);
void						free_interface_registry(t_interface *itf);
void						cleanup_interface(t_registry *shell);
void						prompt_read_failed(t_registry *shell,
								t_vector *vect);
uint32_t					get_next_char(char *str, uint32_t index,
								char direction);
void						shift_content_right_once(t_vector *vect,
								unsigned int cursor);
void						shift_content_left_once(t_vector *vect,
								unsigned int cursor);
/*
*****************************************************
*********************** UTILS ***********************
*****************************************************
*/

int							ft_putc(int c);
int8_t						validate_interface_content(t_interface *itf);
uint8_t						is_printable(char c[READ_SIZE]);
uint8_t						is_eof(char *buffer);
uint32_t					get_prompt_len(t_registry *itf);
uint64_t					compute_mask(char c[READ_SIZE]);
void						reset_vector(t_vector *vect);
void						replace_vector(t_vector *dest, t_vector *src);
void						realloc_vector(t_vector *dest, t_vector *source);
void						move_vector(t_vector *dest, char *src);

/*
*****************************************************
******************** ACTION KEYS ********************
*****************************************************
*/

int8_t						tc_ak_ctrl_d(t_registry *shell);
int8_t						tc_ak_next_word(t_registry *shell);
int8_t						tc_ak_prev_word(t_registry *shell);
int8_t						tc_ak_cut_before_cursor(t_registry *shell);
int8_t						tc_ak_cut_after_cursor(t_registry *shell);
int8_t						tc_ak_copy_before_cursor(t_registry *shell);
int8_t						tc_ak_copy_after_cursor(t_registry *shell);
int8_t						tc_ak_cut_line(t_registry *shell);
int8_t						tc_ak_copy_line(t_registry *shell);
int8_t						tc_ak_paste_clipboard(t_registry *shell);
int8_t						tc_ak_clear_screen(t_registry *shell);
int8_t						tc_ak_home(t_registry *shell);
int8_t						tc_ak_end(t_registry *shell);
int8_t						tc_ak_delete(t_registry *shell);
int8_t						tc_ak_backspace(t_registry *shell);
int8_t						tc_ak_arrow_up(t_registry *shell);
int8_t						tc_ak_arrow_down(t_registry *shell);
int8_t						tc_ak_arrow_left(t_registry *shell);
int8_t						tc_ak_arrow_right(t_registry *shell);
int8_t						tc_ak_hightab(t_registry *shell);
int8_t						tc_ak_ctrl_down(t_registry *shell);
int8_t						tc_ak_ctrl_up(t_registry *shell);

#endif
