# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    run.sh                                             :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/17 09:10:48 by nrechati          #+#    #+#              #
#    Updated: 2019/04/26 10:19:58 by nrechati         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

gcc -o resolve srcs/* ../srcs/resolution/* ../srcs/startup/hash.c ../srcs/startup/utils.c -I ../libft/includes/ ../libft/libft.a -I includes -I../includes
