# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/26 18:34:36 by cempassi          #+#    #+#              #
#    Updated: 2019/04/04 11:46:09 by skuppers         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ! UNUSED !
# ---------------------------------------------------------------------------- #
#								    Version                                    #
# ---------------------------------------------------------------------------- #
VERSION_RELEASE = alpha
VERSION_MAJOR = 0 
VERSION_MINOR = 0
VERSION_PATCH = 0

# ---------------------------------------------------------------------------- #
#								     Build                                     #
# ---------------------------------------------------------------------------- #

BUILD_NUMBER_FILE = "./.build-number"
BUILD_NUMBER = `cat $(BUILD_NUMBER_FILE)`

NUMBER_INC = $(shell echo "$(BUILD_NUMBER) + 1 "| bc)

# ---------------------------------------------------------------------------- #
#								 Build Targets                                 #
# ---------------------------------------------------------------------------- #

NAME = 42sh
NAMEDB = 42shdb
NAMET = unit
LIBFT = libft.a
LIBFTDB = libftdb.a
OBJL = $(patsubst %.c, $(OPATH)%.o, $(LINE) $(LINEM))
OBJT = $(patsubst %.c, $(OPATH)%.o, $(LINE) $(UNIT) $(UNITM))
OBJD = $(patsubst %.c, $(OPATH)db%.o, $(LINE) $(LINEM))
LIB = $(addprefix $(LPATH), $(LIBFT))
LIBDB = $(addprefix $(LPATH), $(LIBFTDB))
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
TOUCH = touch

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
TPATH = unit-tests
_SPATH += interface
_SPATH += interface/action_keys
_SPATH += interface/action_keys/clipboard
_SPATH += interface/action_keys/movement
_SPATH += interface/core
_SPATH += interface/init
_SPATH += interface/misc
_SPATH += interface/redraw
_SPATH += interface/utils
_SPATH += logging
_SPATH += signals
_SPATH += startup
SPATH += $(addprefix srcs/, $(_SPATH))

# ---------------------------------------------------------------------------- #
#									 vpath                                     #
# ---------------------------------------------------------------------------- #

vpath %.c $(SPATH) $(TPATH)
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
#CFLAGS += -Werror
CFLAGS += $(IFLAGS)
DFLAGS = $(CFLAGS) -fsanitize=address
LFLAGS = -ltermcap

# ---------------------------------------------------------------------------- #
#									Includes                                   #
# ---------------------------------------------------------------------------- #

INCS += 21sh.h
INCS += log.h
INCS += line_edit.h

INCS += unit.h

# ---------------------------------------------------------------------------- #
#									Sources                                    #
# ---------------------------------------------------------------------------- #

#							- - - - - Main - - - - -                           #
UNITM = unit.c
LINEM = main.c

#						- - - - -  Unit-test  - - - - -
UNIT += clipboard_tests.c

#						- - - - -   Startup   - - - - -

LINE += launch.c
LINE += free.c
LINE += utils.c
LINE += internals.c

#						- - - - -  Debug Log  - - - - -

LINE += debug_logger.c

#						- - - - - Line edtion - - - - -                        #

#Signals
LINE += signal_handler.c

#Utilities
LINE += move_tools.c
LINE += clean_registry.c
LINE += ft_putc.c
LINE += set_quote.c
LINE += shift_tools.c

#Misc
LINE += prompt_errors.c

#Redraw
LINE += clean_screen.c
LINE += redraw_prompt.c

#Initialization
LINE += load_interface_config.c
LINE += load_termcap_strings.c

#Core 
LINE += invoke_interactive.c
LINE += prompt.c
LINE += sub_prompt.c
LINE += validate_quoting.c
LINE += handle_input_keys.c
LINE += window.c

#Action keys
LINE += init_clipboard.c
LINE += init_ak_keycodes.c
LINE += execute_clipboard_copy_ak.c
LINE += execute_clipboard_cut_ak.c
LINE += execute_clipboard_paste.c
LINE += execute_arrow_ak.c
LINE += execute_he_ak.c
LINE += execute_word_jumping_ak.c
LINE += execute_ctrl_ak.c
LINE += execute_special_ak.c

# ---------------------------------------------------------------------------- #
#									 Rules                                     #
# ---------------------------------------------------------------------------- #

all : $(NAME)

debug : $(NAMEDB)

test : $(NAMET)
	./$<

#					 - - - - - Normal Compilation - - - - -                    #

$(NAME) : $(CLEAR) $(LIB) $(OPATH) $(OBJL) 
	@$(shell if ! test -f $(BUILD_NUMBER_FILE); then echo 0 > $(BUILD_NUMBER_FILE); fi)
	@echo "$(NUMBER_INC)" > $(BUILD_NUMBER_FILE)
	$(LINK) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $(LDLIBN) $(LFLAGS) -DBUILD=$(BUILD_NUMBER) -o  $@ $(OBJL)
	$(PRINT) "$(GREEN)$@ build $(BUILD_NUMBER) is ready $(NC)"

$(OBJL) : $(OPATH)%.o : %.c $(INCS) 
	$(COMPILE) $(CFLAGS) $(CPPFLAGS) $< -o $@
	$(PRINT) "$(ONELINE)$(BLUE)Compiling $<                   $(NC)\n"
	
$(LIB) : FORCE
	$(MAKE) -C $(LPATH)

#					 - - - - Unit test Compilation - - - -                     #

$(NAMET) : $(CLEAR) $(LIB) $(OPATH) $(OBJT) 
	@$(shell if ! test -f $(BUILD_NUMBER_FILE); then echo 0 > $(BUILD_NUMBER_FILE); fi)
	@echo "$(NUMBER_INC)" > $(BUILD_NUMBER_FILE)
	$(LINK) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $(LDLIBN) $(LFLAGS) -fsanitize=address -o  $@ $(OBJT)
	$(PRINT) "$(GREEN)$@ build $(BUILD_NUMBER) is ready $(NC)"

$(OBJT) : $(OPATH)%.o : %.c $(INCS) 
	$(COMPILE) $(CFLAGS) $(CPPFLAGS) $< -o $@
	$(PRINT) "$(ONELINE)$(BLUE)Compiling $<                   $(NC)\n"

#					 - - - - - Debug Compilation - - - - -                     #

$(NAMEDB) : $(CLEAR) $(LIBDB) $(OPATH) $(OBJD) 
	$(LINKD) $(DFLAGS) $(CPPFLAGS) $(LDFLAGS) $(LDLIBD) $(LFLAGS) -o $@ $(OBJD)
	$(PRINT) "$(GREEN)$@ is ready $(NC)"

$(OBJD) : $(OPATH)db%.o : %.c $(INCS) 
	$(DEBUG) $(DFLAGS) $(CPPFLAGS) $< -o $@
	$(PRINT) "$(ONELINE)$(BLUE)Compiling $< for debug                   $(NC)\n"

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
