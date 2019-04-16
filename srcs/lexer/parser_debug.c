#include "parser.h"

void		print_token_debug(t_token *token)
{
	static int	legacy = -1;
	const static char *script[14] = {CASE, DO, DONE, ELIF, ELSE, ESAC, FI, FOR
									, IF, IN, THEN, UNTIL, WHILE};
	const static char *leg_type[3] = {"Command", "Option", "Argument" };

	if (token->type == E_STRING || token->type == E_QUOTE || token->type == E_DB_QUOTE)
	{
		if (legacy == -1)
			legacy = 0;
		else if (legacy == 0)
			legacy = *token->data == '-' ? 1 : 2;
		else if (legacy == 1 && (*token->data != '-'))
			legacy = 2;
	}
	else
		legacy = -1;
	if (token->type == E_STRING || token->type == E_QUOTE 
		|| token->type == E_DB_QUOTE)
		ft_printf("\033[37m         --------\n         |   %c  | data [%s] | type [%s]\n         --------\n", token->type == E_STRING ? 'S' : ALLCHAR[token->type], token->data, leg_type[legacy]);
	else if (token->type < 24)
		ft_printf("\033[37m         --------\n         |   %c  |\n         --------\n", 		ALLCHAR[token->type]);
	else
		ft_printf("\033[37m         --------\n         | %-5s|\n         --------\n", script[token->type - 24]);
	if (ft_strequ(token->data, "--"))
		legacy = 2;
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
	else if (which == 1)
		ft_printf("\033[31m ==> ERROR: miss token type %d\n\033[0m", type);
	else
		ft_printf("\033[31m ==> ERROR: parsing error\n\033[0m");
}

void		print_result_debug(int which)
{
	if (which == 0)
		ft_printf("\033[32m         --------\n         |  OK  |\n         --------\n\n\033[0m");
	else
		ft_printf("\033[31m         --------\n         |  KO  |\n         --------\n\n\033[0m");
}
