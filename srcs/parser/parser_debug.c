#include "parser.h"

void		print_token_debug(t_token *token)
{
	const static char *signs[14] = {"&&", "OR", ";;", "<<", ">>", "<&", ">&"
		, "<>", "<<-", ">|", "==", "!="};
	const static char *script[14] = {CASE, DO, DONE, ELIF, ELSE, ESAC, FI, FOR
									, IF, IN, THEN, UNTIL, WHILE};

	if (token->type == E_STRING || token->type == E_QUOTE 
		|| token->type == E_DB_QUOTE || token->type == E_EXP)
		ft_printf("\033[37m         --------\n         |   %c   | data [%s]\n         --------\n",
				token->type < SINGLE_SIGNS ? ALLCHAR[token->type] : 'S', token->data);
	else if (token->type < SINGLE_SIGNS)
		ft_printf("\033[37m         --------\n         |   %c   |\n         --------\n",
				ALLCHAR[token->type]);
	else if (token->type >= SINGLE_SIGNS && token->type < SIGNS)
		ft_printf("\033[37m         --------\n         | %5s |\n         --------\n", signs[token->type - SINGLE_SIGNS]);
	else if (token->type >= SIGNS && token->type < SIGNS + 13)
		ft_printf("\033[37m         --------\n         | %5s |\n         --------\n", script[token->type - SIGNS]);
	else if (token->type == E_IO_NUMBER)
		ft_printf("\033[37m         --------\n         |   IO   |\n         --------\n");
	else if (token->type == E_ASSIGN)
		ft_printf("\033[37m         --------\n         |ASSIGN| data [%s]\n         --------\n", token->data);
	else
		ft_printf("\033[37m         --------\n         |  END  |\n         --------\n");
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
