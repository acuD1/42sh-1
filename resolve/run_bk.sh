# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    run.sh                                             :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/17 09:10:48 by nrechati          #+#    #+#              #
#    Updated: 2019/04/26 09:35:04 by skuppers         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

gcc -fsanitize=address -o resolve -ltermcap ../srcs/interface/redraw/* ../srcs/lexer/* ../srcs/parser/* ../srcs/interface/misc/* ../srcs/interface/core/* ../srcs/interface/action_keys/movement/* ../srcs/interface/action_keys/clipboard/* ../srcs/interface/action_keys/execute_ctrl_ak.c  ../srcs/interface/action_keys/execute_special_ak.c ../srcs/interface/action_keys/init_ak_keycodes.c ../srcs/interface/utils/* ../srcs/interface/init/* ../srcs/signals/*  ../srcs/logging/* ../srcs/startup/* ../srcs/builtin/* ../srcs/resolution/* ../srcs/interface/utils/* srcs/* -I ../libft/includes/ ../libft/libft.a -I includes -I../includes
