# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    run.sh                                             :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/17 09:10:48 by nrechati          #+#    #+#              #
#    Updated: 2019/04/22 07:03:15 by skuppers         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

gcc -fsanitize=address -o job srcs/* -I ../libft/includes/ ../libft/libft.a -I includes -I../includes
