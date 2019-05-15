#include "sh21.h"
#include "interface_functions.h"

uint64_t    assign_keycodes(t_interface *itf)
{
	itf->ak_masks[AK_ARROW_RIGHT] = AK_ARROW_RIGHT_MASK;
	itf->ak_masks[AK_ARROW_LEFT] = AK_ARROW_LEFT_MASK;
	itf->ak_masks[AK_ARROW_UP] = AK_ARROW_UP_MASK;
	itf->ak_masks[AK_ARROW_DOWN] = AK_ARROW_DOWN_MASK;
	itf->ak_masks[AK_HOME] = AK_HOME_MASK;
	itf->ak_masks[AK_END] = AK_END_MASK;
	itf->ak_masks[AK_BACKSPACE] = AK_BACKSPACE_MASK;
	itf->ak_masks[AK_DELETE] = AK_DELETE_MASK;
	itf->ak_masks[AK_CTRL_A] = AK_CTRL_A_MASK;
	itf->ak_masks[AK_CTRL_D] = AK_CTRL_D_MASK;
	itf->ak_masks[AK_CTRL_E] = AK_CTRL_E_MASK;
	itf->ak_masks[AK_CTRL_L] = AK_CTRL_L_MASK;
	itf->ak_masks[AK_CTRL_X] = AK_CTRL_X_MASK;
	itf->ak_masks[AK_CTRL_B] = AK_CTRL_B_MASK;
	itf->ak_masks[AK_CTRL_P] = AK_CTRL_P_MASK;
	itf->ak_masks[AK_CTRL_LB] = AK_CTRL_LB_MASK;
	itf->ak_masks[AK_CTRL_RB] = AK_CTRL_RB_MASK;
	itf->ak_masks[AK_CTRL_F] = AK_CTRL_F_MASK;
	itf->ak_masks[AK_CTRL_R] = AK_CTRL_R_MASK;
	itf->ak_masks[AK_CTRL_LEFT] = AK_CTRL_LEFT_MASK;
	itf->ak_masks[AK_CTRL_RIGHT] = AK_CTRL_RIGHT_MASK;
	itf->ak_masks[AK_TABULATION] = AK_TAB_MASK;
	itf->ak_masks[AK_CTRL_DOWN] = AK_CTRL_DOWN_MASK;
	itf->ak_masks[AK_CTRL_UP] = AK_CTRL_UP_MASK;
    return (SUCCESS);
}

uint64_t    link_keys_functions(int8_t (*tc_call[AK_AMOUNT])(t_registry *shell))
{
    tc_call[AK_ARROW_LEFT] = &tc_ak_arrow_left;
	tc_call[AK_ARROW_RIGHT] = &tc_ak_arrow_right;
	tc_call[AK_ARROW_UP] = &tc_ak_arrow_up;
	tc_call[AK_ARROW_DOWN] = &tc_ak_arrow_down;
	tc_call[AK_HOME] = &tc_ak_home;
	tc_call[AK_END] = &tc_ak_end;
	tc_call[AK_BACKSPACE] = &tc_ak_backspace;
	tc_call[AK_DELETE] = &tc_ak_delete;
	tc_call[AK_CTRL_A] = &tc_ak_home;
	tc_call[AK_CTRL_D] = &tc_ak_ctrl_d;
	tc_call[AK_CTRL_E] = &tc_ak_end;
	tc_call[AK_CTRL_X] = &tc_ak_cut_line;
	tc_call[AK_CTRL_B] = &tc_ak_copy_line;
	tc_call[AK_CTRL_P] = &tc_ak_paste_clipboard;
	tc_call[AK_CTRL_L] = &tc_ak_clear_screen;
	tc_call[AK_CTRL_RB] = &tc_ak_copy_after_cursor;
	tc_call[AK_CTRL_LB] = &tc_ak_copy_before_cursor;
	tc_call[AK_CTRL_F] = &tc_ak_cut_before_cursor;
	tc_call[AK_CTRL_R] = &tc_ak_cut_after_cursor;
	tc_call[AK_CTRL_LEFT] = &tc_ak_prev_word;
	tc_call[AK_CTRL_RIGHT] = &tc_ak_next_word;
	tc_call[AK_TABULATION] = &tc_ak_hightab;
	tc_call[AK_CTRL_UP] = &tc_ak_ctrl_up;
	tc_call[AK_CTRL_DOWN] = &tc_ak_ctrl_down;
    return (SUCCESS);
}

uint64_t    set_interface_internals(t_registry *shell)
{
	if (add_internal(shell, INT_PS1, INT_PS1_VALUE) == FAILURE)
		return (INTERNAL_FAIL);
	if (add_internal(shell, INT_PS2, INT_PS2_VALUE) == FAILURE)
		return (INTERNAL_FAIL);
	if (add_internal(shell, INT_PS3, INT_PS3_VALUE) == FAILURE)
		return (INTERNAL_FAIL);
	if (add_internal(shell, INT_PS4, INT_PS4_VALUE) == FAILURE)
		return (INTERNAL_FAIL);
    return (SUCCESS);
}

uint64_t    init_line(t_interface *interface)
{
	if ((interface->line = vct_new(0)) == NULL)
		return (CRITICAL_ERROR | LINE_FAIL);
	if ((interface->sub_line = vct_new(0)) == NULL)
		return (CRITICAL_ERROR | LINE_FAIL);
    return (SUCCESS);
}