/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_edit.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 09:33:05 by skuppers          #+#    #+#             */
/*   Updated: 2019/03/28 18:46:57 by skuppers         ###   ########.fr       */
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
#include "libft.h"
#include "21sh.h"
#include "history.h"

# define READ_SIZE 8
# define AK_AMOUNT 25

/*  A RAJOUTER */
# define LINE_BUFFER_SIZE 16 // Taille du buffer pour la lecture du clavier, en characteres
# define CLIPBOARD_SIZE	256  // Taille du presse-papier interne, en characteres
# define BUFFER_SCALE_MULT 2 // Multiplicateur pour le resize des vecteurs LINE_BUFFER ET CLIPBOARD

# define PROMPT_TEXT "[21sh] -> " // Texte PS1

# define PROMPT_TEXT_LENGTH 10    // Definis la taille du PS1 - DOIT ETRE CORRECTE
							      // Doit etre recalculer si PROMPT_TEXT change

# define PS2_TEXT "quote> "       // TEXTE PS2
# define PS2_TEXT_LENGTH 7		  // Definis la taille du PS2 - DOIT ETRE CORRECTE
								  // Doit etre recalculer si PS2_TEXT change

# define IFS_CHARACTER 10		// Charactere de separation (10 = \n) // Preferable de la mettre en READ-ONLY
# define ESCAPE_CHAR '\\'       // Character d'echapement (Non-implemente encore) // A voir si on la met en READ-ONLY ou pas

# define MAGIC_NUMBER 42424242  // Numero magique pour la gestion de certain cas specifique aux
								// signaux et l'edition de ligne quand PS2 est actif

enum interface_states {
	PS1,
	PS2,
};

enum action_keys {
	AK_ENTER,
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
	AK_CTRL_X, //cut all
	AK_CTRL_B, //copy all
	AK_CTRL_P, //paste clipboard
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
	char		*clear;
	char		*begin_insertion; //im
	char		*end_insertion; //ei
	char		*cs_down; //do
	char		*cs_right; //nd
	char		*cs_left; //le
	char		*cs_up; //up
}				t_termcaps;

typedef struct s_winsize
{
	unsigned int	x;
	unsigned int	y;
	unsigned int	rows;
	unsigned int	cols;
	int				max_line_len;
	int				cursor_index;
}				t_winsize;

typedef struct	s_interface_registry
{
	t_vector			*clipboard;
	t_vector			*vector;
	t_termcaps			*termcaps;
	t_winsize			*window;

	t_history			*history_head;
	t_history			*history_ptr;

	struct termios		*orig_term;
	struct termios		*new_term;

	int					interface_state;
	int					ak_keycodes[AK_AMOUNT][READ_SIZE];
	int					(*tc_call[AK_AMOUNT])(struct s_interface_registry *itf_reg);
}						t_interface_registry;

extern	t_interface_registry *g_interface_registry_pointer;

void					redraw_prompt(int signo);

void					free_interface_registry(t_interface_registry *itf_reg);

int						invoke_ps2_prompt(t_registry *sh, t_interface_registry *itf);
void					validate_input_quoting(t_registry *sh_reg, t_interface_registry *itf_reg);

int						replace_input_line(char *string, t_interface_registry *itf_reg);

void					cleanup_interface_registry(t_interface_registry *itf_reg);

void					define_interface_signal_behavior(t_interface_registry *itf_reg, t_registry *shell_reg);

void					init_ak_keycodes(t_interface_registry *itf_reg);

void					launch_shell_prompt(t_registry *reg, t_interface_registry *itf_registry);
char					*prompt(t_registry *shell_reg, t_interface_registry *itf_reg);
void					prompt_read_failed(t_registry *reg, t_vector *vect);

void					print_words(char *str, t_interface_registry *itf_reg);

int						redraw_input_line(t_interface_registry *itf_reg);
int						redraw_after_cursor(t_interface_registry *itf_reg);

t_termcaps				*init_termcap_calls(t_registry *reg);
t_interface_registry	*init_line_edition(t_registry *reg);
int						handle_input_key(char c[], t_interface_registry *itf_reg);
void					vector_rescale(t_vector *buffer);
size_t					vector_last_char(t_vector *vector);
void					shift_content_right_once(t_vector *vect, unsigned int cursor_index);
void					shift_content_left_once(t_vector *vect, unsigned int cursor_index);
int						ft_putc(int c);
void					init_termcap_actions(int (*tc_call[AK_AMOUNT])(t_interface_registry *itf_registry));

t_vector				*allocate_clipboard(t_registry *sh_reg);

void					restore_original_term_behavior(t_registry *sh_reg, t_interface_registry *itg_re);

//unsigned int	handle_printable_char(char c[READ_SIZE]);

void			init_ak_home(t_interface_registry *itf_reg);
void			init_ak_end(t_interface_registry *itf_reg);
void			init_ak_backspace(t_interface_registry *itf_reg);
void			init_ak_delete(t_interface_registry *itf_reg);
void			init_ak_enter(t_interface_registry *itf_reg);
void			init_ak_arrow_up(t_interface_registry *itf_reg);
void			init_ak_arrow_down(t_interface_registry *itf_reg);
void			init_ak_arrow_left(t_interface_registry *itf_reg);
void			init_ak_arrow_right(t_interface_registry *itf_reg);
void			init_ak_ctrl_a(t_interface_registry *itf_reg);
void			init_ak_ctrl_d(t_interface_registry *itf_reg);
void			init_ak_ctrl_e(t_interface_registry *itf_reg);
void			init_ak_ctrl_l(t_interface_registry *itf_reg);
void			init_ak_ctrl_x(t_interface_registry *itf_reg);
void			init_ak_ctrl_b(t_interface_registry *itf_reg);
void			init_ak_ctrl_p(t_interface_registry *itf_reg);
void			init_ak_escape(t_interface_registry *itf_reg);
void			init_ak_ctrl_rb(t_interface_registry *itf_reg);
void			init_ak_ctrl_lb(t_interface_registry *itf_reg);
void			init_ak_ctrl_f(t_interface_registry *itf_reg);
void			init_ak_ctrl_r(t_interface_registry *itf_reg);
void			init_ak_ctrl_left(t_interface_registry *itf_reg);
void			init_ak_ctrl_right(t_interface_registry *itf_reg);
void			init_ak_hightab(t_interface_registry *itf_reg);
void			init_ak_ctrl_up(t_interface_registry *itf_reg);
void			init_ak_ctrl_down(t_interface_registry *itf_reg);

int				tc_ak_ctrl_d(t_interface_registry *itf_registry);
int				tc_ak_next_word(t_interface_registry *itf_registry);
int				tc_ak_prev_word(t_interface_registry *itf_registry);
int				tc_ak_cut_before_cursor(t_interface_registry *itf_registry);
int				tc_ak_cut_after_cursor(t_interface_registry *itf_registry);
int				tc_ak_copy_before_cursor(t_interface_registry *itf_registry);
int				tc_ak_copy_after_cursor(t_interface_registry *itf_registry);
int				tc_ak_cut_line(t_interface_registry *itf_registry);
int				tc_ak_copy_line(t_interface_registry *itf_registry);
int				tc_ak_paste_clipboard(t_interface_registry *itf_registry);
int				tc_ak_clear_screen(t_interface_registry *itf_registry);
int				tc_ak_enter(t_interface_registry *itf_registry);
int				tc_ak_home(t_interface_registry *itf_registry);
int				tc_ak_end(t_interface_registry *itf_registry);
int				tc_ak_delete(t_interface_registry *itf_registry);
int				tc_ak_backspace(t_interface_registry *itf_registry);
int				tc_ak_arrow_up(t_interface_registry *itf_registry);
int				tc_ak_arrow_down(t_interface_registry *itf_registry);
int				tc_ak_arrow_left(t_interface_registry *itf_registry);
int				tc_ak_arrow_right(t_interface_registry *itf_registry);
int				tc_ak_hightab(t_interface_registry *itf_registry);
int				tc_ak_ctrl_down(t_interface_registry *itf_registry);
int				tc_ak_ctrl_up(t_interface_registry *itf_registry);

#endif
