# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/26 18:34:36 by cempassi          #+#    #+#              #
#    Updated: 2019/03/26 22:01:22 by cempassi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ---------------------------------------------------------------------------- #
#								 Build Targets                                 #
# ---------------------------------------------------------------------------- #

NAME = 42sh
NAMEDB = 42shdb
LIBFT = libft.a
LIBFTDB = libftdb.a
OBJS = $(patsubst %.c, $(OPATH)%.o, $(SRCS))
OBJD = $(patsubst %.c, $(OPATH)db%.o, $(SRCS))
LIB = $(addprefix $(LPATH), $(LIBFT))
LIBDB = $(addprefix $(LPATH), $(LIBFTDB))
SRCS += $(LINE)

# ---------------------------------------------------------------------------- #
#									Compiler                                   #
# ---------------------------------------------------------------------------- #

CC = Clang
LINK = $(CC)
LINKD = $(CC) -g3
COMPILE = $(CC) -c
DEBUG = $(CC) -g3 -c

# ---------------------------------------------------------------------------- #
#									Commands                                   #
# ---------------------------------------------------------------------------- #

MKDIR = mkdir -p
CLEANUP = rm -rf
PRINT = printf
CLEAR = clear

# ---------------------------------------------------------------------------- #
#									 Output                                    #
# ---------------------------------------------------------------------------- #

# One Line 
ONELINE =\e[1A\r

# Colors
NC = \033[0m
BLACK = \033[0;30m
RED = \033[0;31m
GREEN = \033[32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
PURPLE = \033[0;35m
CYAN = \033[0;36m
WHITE = \033[0;37m

# ---------------------------------------------------------------------------- #
#								  Directories                                  #
# ---------------------------------------------------------------------------- #

LPATH = libft/
OPATH = objs/
IPATH += includes/
IPATH += libft/includes/
_SPATH += interface
_SPATH += interface/core
_SPATH += interface/history
_SPATH += interface/init
_SPATH += interface/misc
_SPATH += interface/utils
_SPATH += logging
_SPATH += signals
_SPATH += startup
SPATH += $(addprefix srcs/, $(_SPATH))

# ---------------------------------------------------------------------------- #
#									 vpath                                     #
# ---------------------------------------------------------------------------- #

vpath %.c $(SPATH)
vpath %.h $(IPATH)

# ---------------------------------------------------------------------------- #
#							   Compilation Flags                               #
# ---------------------------------------------------------------------------- #

IFLAGS = $(addprefix -I, $(IPATH))
LDLIBN = -lft
LDLIBD = -lftdb
LDFLAGS = -L $(LPATH)
CFLAGS += -Wall
CFLAGS += -Wextra
CFLAGS += -Werror
CFLAGS += $(IFLAGS)
DFLAGS = $(CFLAGS) -fsanitize=address
LFLAGS = -ltermcap

# ---------------------------------------------------------------------------- #
#									Includes                                   #
# ---------------------------------------------------------------------------- #

INCS += 21sh.h
INCS += line_edit.h
INCS += log.h
INCS += history.h
INCS += startup.h

# ---------------------------------------------------------------------------- #
#									Sources                                    #
# ---------------------------------------------------------------------------- #

#						- - - - - Line edtion - - - - -                        #

LINE += execute_arrow_ak.c
LINE += execute_ctrl_ak.c
LINE += execute_special_ak.c
LINE += handle_input_keys.c
LINE += prompt.c
LINE += redraw_prompt.c
LINE += sub_shell.c
LINE += validate_quoting.c
LINE += command_history.c
LINE += init_special_ak.c
LINE += init_ctrl_ak.c
LINE += init_arrow_ak.c
LINE += init_clipboard.c
LINE += init_ak_keycodes.c
LINE += load_termcap_strings.c
LINE += load_interface_config.c
LINE += keymap_handler.c
LINE += prompt_errors.c
LINE += debug_logger.c
LINE += file_logger.c
LINE += clean_registry.c
LINE += shift_tools.c
LINE += 21sh.c
LINE += argument_parser.c
LINE += environment_parser.c
LINE += startup_initialisation.c
LINE += workspace.c
LINE += signal_handler.c

# ---------------------------------------------------------------------------- #
#									 Rules                                     #
# ---------------------------------------------------------------------------- #

all : $(NAME)

debug : $(NAMEDB)

#					 - - - - - Normal Compilation - - - - -                    #

$(NAME) : $(CLEAR) $(LIB) $(OPATH) $(OBJS) 
	$(LINK) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $(LDLIBN) $(LFLAGS) -o $@ $(OBJS)
	$(PRINT) "$(GREEN)$@ is ready $(NC)"

$(OBJS) : $(OPATH)%.o : %.c $(INCS) 
	$(COMPILE) $(CFLAGS) $(CPPFLAGS) $< -o $@
	$(PRINT) "$(ONELINE)$(BLUE)Compiling $<             $(NC)\n"
	
$(LIB) : FORCE
	$(MAKE) -C $(LPATH)

#					 - - - - - Debug Compilation - - - - -                     #

$(NAMEDB) : $(CLEAR) $(LIBDB) $(OPATH) $(OBJD) 
	$(LINKD) $(DFLAGS) $(CPPFLAGS) $(LDFLAGS) $(LDLIBD) $(LFLAGS) -o $@ $(OBJD)
	$(PRINT) "$(GREEN)$@ is ready $(NC)"

$(OBJD) : $(OPATH)db%.o : %.c $(INCS) 
	$(DEBUG) $(DFLAGS) $(CPPFLAGS) $< -o $@
	$(PRINT) "$(ONELINE)$(BLUE)Compiling $< for debug            $(NC)\n"

$(LIBDB) : FORCE
	$(MAKE) -C $(LPATH) debug

$(CLEAR):
	$@

$(OPATH) :
	$(MKDIR) $(OPATH)

clean :
	$(MAKE) -C $(LPATH) clean
	$(CLEANUP) $(OPATH)
	$(PRINT) ".o file deleted\n"

fclean : clean
	$(MAKE) -C $(LPATH) fclean
	$(CLEANUP) $(NAME)
	$(CLEANUP) $(NAMEDB)
	$(PRINT) "Executables destroyed\n"

re : fclean all

help :
	@$(PRINT) "Rules available : all, clean,  fclean, re, and help\n"

FORCE:

.PHONY : all clean fclean re help FORCE
.SILENT:
