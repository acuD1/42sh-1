#include "sh21.h"
#include "interface_functions.h"
#include <termcap.h>


static uint8_t		get_input(t_registry *shell, t_vector **in)
{
	*in = prompt(shell, INT_PS1);

	if (*in == NULL)
		return (FAILURE); // read fail / Malloc fail

	if (ft_strequ(vct_get_string(*in), "\0"))
		return (LINE_FAIL);

//	if (is_eof(vct_get_string(input)))
//		return (FAILURE);

//	if ((*in = vct_dup(input)) == NULL)
//		return (FAILURE);

	return (SUCCESS);
}

void				interactive_mode(t_registry *shell)
{
	uint8_t			valid;
	t_vector		*input;

	valid = 0;
	input = NULL;
	while (1)
	{
		valid = get_input(shell, &input);

		if (valid != SUCCESS && valid != LINE_FAIL)
			return ;
		ft_dprintf(2, "\nSLE sending: |%s|\n", vct_get_string(input));
//		execution_pipeline(shell,
//				lexer(&shell->lexinfo, vct_get_string(input)));
	}

// default signals
	restore_term_behavior(shell);
}
