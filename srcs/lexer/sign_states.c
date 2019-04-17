/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sign_states.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 18:56:27 by cempassi          #+#    #+#             */
/*   Updated: 2019/04/17 14:09:41 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	double_sign_machine(t_machine *machine)
{
	int		checker;

	checker = 0;
	if (ft_strchr(DOUBLE_SIGN, *machine->input))
	{
		if (*machine->buffer == '|' && *machine->input == '|' && ++checker)
			machine->last_machine = E_OR;
		else if (*machine->buffer == ';' && *machine->input == ';' && ++checker)
			machine->last_machine = E_DSEMI;
		else if (*machine->buffer == '&' && *machine->input == '&' && ++checker)
			machine->last_machine = E_DAND;
		else if (*machine->buffer == '=' && *machine->input == '=' && ++checker)
			machine->last_machine = E_DEQ;
		else if (*machine->buffer == '!' && *machine->input == '=' && ++checker)
			machine->last_machine = E_NOTEQ;
		if (checker)
			machine->input++;
	}
	if (*machine->buffer == '=' && *machine->input != '=')
		machine->state = LETTER;
	else
		machine->state = OUT;
}

void	lesser_machine(t_machine *machine)
{
	int		checker;

	checker = 0;
	if (machine->last_machine == E_DLESS && *machine->input == '-' && ++checker)
		machine->last_machine = E_DLESSDASH;
	else if (*machine->buffer == '<' && *machine->input == '<')
	{
		if (machine->last_machine != E_DLESS)
		{
			machine->last_machine = E_DLESS;
			ft_strncat(machine->buffer, machine->input, 1);
			machine->input++;
			return ;
		}
	}
	else if (*machine->input == '>' || *machine->input == '&')
	{
		if (*machine->buffer == '<' && *machine->input == '&' && ++checker)
			machine->last_machine = E_LESSAND;
		else if (*machine->buffer == '<' && *machine->input == '>' && ++checker)
			machine->last_machine = E_LESSGREAT;
	}
	if (checker)
		machine->input++;
	machine->state = OUT;
}

void	greater_machine(t_machine *machine)
{
	int		checker;

	checker = 0;
	if (ft_strchr(">&|", *machine->input))
	{
		if (*machine->buffer == '>' && *machine->input == '>' && ++checker)
			machine->last_machine = E_DGREAT;
		else if (*machine->buffer == '>' && *machine->input == '&' && ++checker)
			machine->last_machine = E_GREATAND;
		else if (*machine->buffer == '>' && *machine->input == '|' && ++checker)
			machine->last_machine = E_CLOBBER;
		if (checker)
			machine->input++;
	}
	machine->state = OUT;
}

int		double_dispatcher(t_machine *machine)
{
	int		checker;

	checker = 0;
	if (*machine->input == '>')
	{
		checker++;
		machine->state = GREATER;
	}
	else if (*machine->input == '<')
	{
		checker++;
		machine->state = LESSER;
	}
	else if (ft_strchr(DOUBLE_SIGN, *machine->input))
	{
		checker++;
		machine->state = DSIGN;
	}
	return (checker);
}

void	sign_machine(t_machine *machine)
{
	if (*machine->input == '\\')
		machine->state = BSL;
	else if (*machine->input == '\'')
		machine->state = SQTE;
	else if (*machine->input == '\"')
		machine->state = DQTE;
	else if (*machine->input == '$')
		machine->state = EXP;
	else if (double_dispatcher(machine))
		ft_strncat(machine->buffer, machine->input, 1);
	else
		fill_buffer_output(machine);
	machine->input++;
}
