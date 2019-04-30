# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    run.sh                                             :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/17 09:10:48 by nrechati          #+#    #+#              #
#    Updated: 2019/04/29 14:05:49 by nrechati         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

gcc -o resolve srcs/* ../srcs/resolution/* ../srcs/builtin/hash_blt.c ../srcs/utils.c -I ../libft/includes/ ../libft/libft.a -I includes -I../includes
