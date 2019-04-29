/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_quote.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 13:14:13 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/27 15:52:20 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	set_quote(char c)
{
	if (c == '\'' || c == '\"' || c == '`')
		return (c);
	return (0);
}
