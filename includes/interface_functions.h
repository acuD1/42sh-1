/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface_functions.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 15:54:02 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/20 06:18:17 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef H_INTERFACE_FUNCTIONS
# define H_INTERFACE_FUNCTIONS

# include "21sh.h"

/*
**	Unit testing
*/

int8_t	fill_interface_data(t_registry *shell);

extern t_registry	*g_shell_registry;

int							init_termcap_calls(t_registry *shell);
int							init_line_edition(t_registry *shell);

short						set_term_behavior(t_registry *shell);
short						restore_term_behavior(t_registry *shell);

int8_t	 					init_window(t_registry *shell, t_interface *itf);
int8_t						init_cursor(t_registry *shell);

void						define_interface_default_signals(t_registry *shell);
void						define_interface_signal_behavior(t_registry *shell);

int8_t						invoke_sub_prompt(t_registry *shell,
							int8_t (*condition)(char *), char *orig_state, char *p_state);

int							launch_shell_prompt(t_registry *shelll);
char						*prompt(t_registry *shell, t_interface *itf);

void						init_ak_keycodes(t_interface *itf);

void						init_termcap_actions(t_registry *shell);

void						handle_input_key(char c[], t_registry *shell);
char						set_quote(char c);
void						validate_input_quoting(t_registry *shell, t_interface *itf);

void						print_char(char c, t_interface *itf);
void						print_words(char *str, t_interface *itf);
void						redraw_prompt(int signo);

uint32_t					clean_screen(t_registry *shell);
uint32_t					replace_input_line(char *string, t_registry *shell);
uint32_t					redraw_input_line(t_registry *shell);
uint32_t					redraw_after_cursor(t_registry *shell);

void						free_interface_registry(t_interface *itf);
void						cleanup_interface(t_registry *shell);

void						prompt_read_failed(t_registry *shell, t_vector *vect);

uint32_t					get_next_char(char *str, uint32_t index, char direction);

void						shift_content_right_once(t_vector *vect, unsigned int cursor);
void						shift_content_left_once(t_vector *vect, unsigned int cursor);


/*
**		UTILS
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
**		ACTION KEYS
*/

int8_t							tc_ak_ctrl_d(t_registry *shell);
int8_t							tc_ak_next_word(t_registry *shell);
int8_t							tc_ak_prev_word(t_registry *shell);
int8_t							tc_ak_cut_before_cursor(t_registry *shell);
int8_t							tc_ak_cut_after_cursor(t_registry *shell);
int8_t							tc_ak_copy_before_cursor(t_registry *shell);
int8_t							tc_ak_copy_after_cursor(t_registry *shell);
int8_t							tc_ak_cut_line(t_registry *shell);
int8_t							tc_ak_copy_line(t_registry *shell);
int8_t							tc_ak_paste_clipboard(t_registry *shell);
int8_t							tc_ak_clear_screen(t_registry *shell);
int8_t							tc_ak_home(t_registry *shell);
int8_t							tc_ak_end(t_registry *shell);
int8_t							tc_ak_delete(t_registry *shell);
int8_t							tc_ak_backspace(t_registry *shell);
int8_t							tc_ak_arrow_up(t_registry *shell);
int8_t							tc_ak_arrow_down(t_registry *shell);
int8_t							tc_ak_arrow_left(t_registry *shell);
int8_t							tc_ak_arrow_right(t_registry *shell);
int8_t							tc_ak_hightab(t_registry *shell);
int8_t							tc_ak_ctrl_down(t_registry *shell);
int8_t							tc_ak_ctrl_up(t_registry *shell);

#endif
