# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    run.sh                                             :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/17 09:10:48 by nrechati          #+#    #+#              #
#    Updated: 2019/04/23 17:01:21 by skuppers         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

gcc -fsanitize=address -o resolve srcs/* ../srcs/resolution/* ../srcs/startup/exit.c ../srcs/startup/free.c ../srcs/startup/hash.c ../srcs/startup/launch.c ../srcs/startup/utils.c   -I ../libft/includes/ ../libft/libft.a -I includes -I../includes
