#include "sh21.h"
#include "interface_functions.h"

static uint64_t				init_interface(t_registry *shell)
{
	uint64_t		report;

	report = 0;
	ft_memset(&shell->interface, 0, sizeof(t_interface));
	report |= get_terminal_info(shell);
	report |= set_terminal_mode(shell);
	report |= init_termcaps(&shell->interface.termcaps);
	return (report);
}

static uint64_t				load_interface(t_registry *shell)
{
	uint64_t		report;

	report = 0;
	report |= assign_keycodes(&shell->interface);
	report |= link_keys_functions(shell->interface.tc_call);
	report |= set_interface_internals(shell);
	report |= init_line(&shell->interface);

	ft_memset(&shell->interface.window, 0, sizeof(t_window));
	ft_memset(&shell->interface.cursor, 0, sizeof(t_cursor));
	ft_memset(&shell->interface.prompt, 0, sizeof(t_prompt));

	report |= init_window(shell);
	report |= init_cursor(&shell->interface);
	report |= init_prompt(&shell->interface);

	return (report);
}

static uint64_t				load_interface_modules(t_interface *interface)
{
	uint64_t		report;

	report = 0;
//	report |= load_clipboard();
//	report |= load_history();
//	report |= load_autocomp();
//	report |= load_subprompt();
	return (report);
}

uint64_t				setup_interface(t_registry *shell)
{
	uint64_t		report;

	report = 0;
	report |= init_interface(shell);
	report |= load_interface(shell);
	report |= load_interface_modules(&shell->interface);
	interface_error(report);
	return (report);
}
