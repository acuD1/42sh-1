/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filename_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 04:47:14 by cempassi          #+#    #+#             */
/*   Updated: 2019/05/05 06:18:14 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "unistd.h"

uint8_t	check_access(char *data)
{
	struct stat	stat;

	if (access(data, F_OK) != SUCCESS)
		return (TRUE);
	lstat(data, &stat);
	if (stat.st_mode & S_IFDIR)
		ft_dprintf(2, "21sh: %s: Is a directory\n", data);
	else if (access(data, R_OK) != SUCCESS)
		ft_dprintf(2, "21sh: %s: Permission denied\n", data);
	else
		return (TRUE);
	return (FALSE);
}

void	check_filename(t_parser *parse)
{
	if (parse->token.data == NULL || check_access(parse->token.data) == FALSE)
	{
		error_parser(parse);
		ft_strdel(&parse->token.data);
	}
	else
		ft_stckpush(&parse->stack, &parse->token, sizeof(t_token));
}

void	filename_parser(t_parser *parse)
{
	if (parse->token.type == E_SPSTRING)
		parse->token.data = string_expansion(parse, parse->token.data);
	if (parse->state == P_IO_REDIRECT)
		parse->state = P_IO_FILENAME;
	else if (parse->token.type == E_SPSTRING)
		parse->state = P_SPFILENAME;
	else
		parse->state = P_FILENAME;
	check_filename(parse);
	get_token(parse);
}

int		io_filename_validate(t_parser *parse, char *str)
{
	int		len;

	if (ft_strcheck(str, ft_isdigit) == 1)
	{
		parse->state = P_IO_DUP;
		return (1);
	}
	len = ft_strlen(str);
	str[len - 1] = character_swap(str[len - 1]);
	if (ft_strcheck(str, ft_isdigit) == 1)
	{
		str[len - 1] = character_swap('\0');
		if (str[len - 1] == '-')
		{
			parse->state = P_IO_MOVE;
			return (1);
		}
	}
	str[len - 1] = character_swap('\0');
	error_parser(parse);
	return (0);
}

void	io_dup_move_parser(t_parser *parse)
{
	parse->token.type = E_STRING;
	if ((parse->token.data = string_expansion(parse, parse->token.data)))
	{
		if (io_filename_validate(parse, parse->token.data))
			ft_stckpush(&parse->stack, &parse->token, sizeof(t_token));
		else
			ft_strdel(&parse->token.data);
		get_token(parse);
	}
}
