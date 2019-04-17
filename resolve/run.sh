# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    run.sh                                             :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/17 09:10:48 by nrechati          #+#    #+#              #
#    Updated: 2019/04/17 16:45:26 by skuppers         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

gcc -o resolve srcs/* ../srcs/startup/exit.c ../srcs/startup/free.c ../srcs/startup/hash.c ../srcs/startup/launch.c ../srcs/startup/utils.c   -I ../libft/includes/ ../libft/libft.a -I includes -I../includes
