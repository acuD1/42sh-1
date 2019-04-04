#include "parser.h"

void		print_token_debug(enum e_type type)
{
	const static char *script[14] = {CASE, DO, DONE, ELIF, ELSE, ESAC, FI, FOR
									, IF, IN, THEN, UNTIL, WHILE};
	if (type < 24 || type == E_STRING)
		ft_printf("\033[37m         --------\n         |   %c  |\n         --------\n", type < 25 ? ALLCHAR[type] : 'S');
	else
		ft_printf("\033[37m         --------\n         |  %-3s |\n         --------\n", script[type - 24]);
}

void		print_arrow_debug(int which)
{
	if (which == 0)
		ft_printf("\033[33m            ||\n            vv\n\033[0m");
	else if (which == 1) 
		ft_printf("\033[34m            ||\n            up\n            ||\n            vv\n\033[0m");
	else
		ft_printf("\033[36m            ||\n           down\n            ||\n            vv\n\033[0m");
}

void		print_error_debug(enum e_type type, int which)
{
	if (which == 0)
		ft_printf("\033[31m ==> ERROR: token type %d is not possible\n\033[0m", type);
	else
		ft_printf("\033[31m ==> ERROR: miss token type %d\n\033[0m", type);
}

void		print_result_debug(int which)
{
	if (which == 0)
		ft_printf("\033[32m         --------\n         |  OK  |\n         --------\n\n\033[0m");
	else
		ft_printf("\033[31m         --------\n         |  KO  |\n         --------\n\n\033[0m");
}
