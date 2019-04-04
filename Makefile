# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/26 18:34:36 by cempassi          #+#    #+#              #
#    Updated: 2019/04/02 13:36:36 by cempassi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ---------------------------------------------------------------------------- #
#								 Build Targets                                 #
# ---------------------------------------------------------------------------- #

21SH = 21sh
21SHDB = 21shdb
LEXER = Lexer_test
LEXERDB = Lexerdb
LIBFT = libft.a
LIBFTDB = libftdb.a
21OBJS = $(patsubst %.c, $(OPATH)%.o, $(LINE))
21OBJD = $(patsubst %.c, $(OPATH)db%.o, $(LINE))
LEXOBJS = $(patsubst %.c, $(OPATH)%.o, $(LEX_SRCS))
LEXOBJD = $(patsubst %.c, $(OPATH)db%.o, $(LEX_SRCS))
LIB = $(addprefix $(LPATH), $(LIBFT))
LIBDB = $(addprefix $(LPATH), $(LIBFTDB))
SRCS += $(LINE)

# ---------------------------------------------------------------------------- #
#									Compiler                                   #
# ---------------------------------------------------------------------------- #

CC = clang
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
LINE_PATH += line_edition/interface
LINE_PATH += line_edition/interface/core
LINE_PATH += line_edition/interface/history
LINE_PATH += line_edition/interface/init
LINE_PATH += line_edition/interface/misc
LINE_PATH += line_edition/interface/utils
LINE_PATH += line_edition/logging
LINE_PATH += line_edition/signals
LINE_PATH += line_edition/startup
LEXER_PATH += lexer/
SPATH += $(addprefix srcs/, $(LINE_PATH) $(LEXER_PATH))

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
DFLAGS = $(CFLAGS) -fsanitize=address,undefined
LFLAGS = -ltermcap

# ---------------------------------------------------------------------------- #
#									Includes                                   #
# ---------------------------------------------------------------------------- #

INCS += 21sh.h
INCS += line_edit.h
INCS += log.h
INCS += history.h
INCS += startup.h
INCS += lexer.h

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

#						   - - - - - Lexer - - - - -                           #

LEX_SRCS += lexer.c
LEX_SRCS += parser.c
LEX_SRCS += machine_interface.c
LEX_SRCS += states.c
LEX_SRCS += generate_token.c
LEX_SRCS += quotes_states.c

# ---------------------------------------------------------------------------- #
#									 Rules                                     #
# ---------------------------------------------------------------------------- #

all : 21 lexer

21 : $(21SH)

21debug : $(21SHDB)

lexer : $(LEXER)
	
lexerdb : $(LEXERDB)

#					 - - - - - Normal Compilation - - - - -                    #

$(21SH) : $(CLEAR) $(LIB) $(OPATH) $(21OBJS) 
	$(LINK) $(CFLAGS) $(LDFLAGS) $(LDLIBN) $(LFLAGS) -o $@ $(21OBJS)
	$(PRINT) "$(GREEN)$@ is ready \n$(NC)"

$(21OBJS) : $(OPATH)%.o : %.c $(INCS) 
	$(COMPILE) $(CFLAGS) $(CPPFLAGS) $< -o $@
	$(PRINT) "$(ONELINE)$(BLUE)Compiling $<             $(NC)\n"
	
$(LEXER) : $(CLEAR) $(LIB) $(OPATH) $(LEXOBJS) 
	$(LINK) $(LEXOBJS) $(CFLAGS) $(LDFLAGS) $(LDLIBN) -o $(LEXER)
	$(PRINT) "$(GREEN)$@ is ready \n$(NC)"

$(LEXOBJS) : $(OPATH)%.o : %.c $(INCS) 
	$(COMPILE) $(CFLAGS) $(CPPFLAGS) $< -o $@
	$(PRINT) "$(ONELINE)$(BLUE)Compiling $<             $(NC)\n"

$(LIB) : FORCE
	$(MAKE) -C $(LPATH)

#					 - - - - - Debug Compilation - - - - -                     #

$(21SHDB) : $(CLEAR) $(LIBDB) $(OPATH) $(OBJD) 
	$(LINKD) $(DFLAGS) $(LDFLAGS) $(LDLIBD) $(LFLAGS) -o $@ $(OBJD)
	$(PRINT) "$(GREEN)$@ is ready \n$(NC)"

$(21OBJD) : $(OPATH)db%.o : %.c $(INCS) 
	$(DEBUG) $(DFLAGS) $(CPPFLAGS) $< -o $@
	$(PRINT) "$(ONELINE)$(BLUE)Compiling $< for debug            $(NC)\n"

$(LEXERDB) : $(CLEAR) $(LIB) $(OPATH) $(LEXOBJD) 
	$(LINKD) $(LEXOBJD) $(DFLAGS) $(LDFLAGS) $(LDLIBN) -o $(LEXERDB)
	$(PRINT) "$(GREEN)$@ is ready \n$(NC)"

$(LEXOBJD) : $(OPATH)db%.o : %.c $(INCS) 
	$(DEBUG) $(DFLAGS) $(CPPFLAGS) $< -o $@
	$(PRINT) "$(ONELINE)$(BLUE)Compiling $<             $(NC)\n"

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
	$(CLEANUP) $(21SH)
	$(CLEANUP) $(21SHDB)
	$(CLEANUP) $(LEXER)
	$(CLEANUP) $(LEXERDB)
	$(PRINT) "Executables destroyed\n"

re : fclean all

help :
	@$(PRINT) "Rules available : all, clean,  fclean, re, and help\n"

FORCE:

.PHONY : all 21 21debug lexer lexerdb clean fclean re help FORCE
.SILENT:
