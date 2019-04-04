#include "parser.h"

void		print_token(enum e_type type)
{
	const static char *script[14] = {CASE, DO, DONE, ELIF, ELSE, ESAC, FI, FOR
									, IF, IN, THEN, UNTIL, WHILE};
	if (type < 24 || type == E_STRING)
		ft_printf("\033[37m         --------\n         |   %c  |\n         --------\n", type < 25 ? ALLCHAR[type] : 'S');
	else
		ft_printf("\033[37m         --------\n         |  %-3s |\n         --------\n", script[type - 24]);
}
