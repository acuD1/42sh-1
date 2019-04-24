# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/26 18:34:36 by cempassi          #+#    #+#              #
#    Updated: 2019/04/24 17:37:17 by ffoissey         ###   ########.fr        #
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

#BUILD_NUMBER_FILE = "./.build-number"
#BUILD_NUMBER = `cat $(BUILD_NUMBER_FILE)`

#NUMBER_INC = $(shell echo "$(BUILD_NUMBER) + 1 "| bc)

# ---------------------------------------------------------------------------- #
#								 Build Targets                                 #
# ---------------------------------------------------------------------------- #

NAME = 42sh
NAMEDB = 42shdb
NAMET = unit
LIBFT = libft.a
LIBFTDB = libftdb.a
OBJM = $(patsubst %.c, $(OPATH)%.o, $(LINEM))
OBJS = $(patsubst %.c, $(OPATH)%.o, $(LINE) $(LEX_SRCS) $(PARSER_SRCS) $(BUILTIN))
OBJT = $(patsubst %.c, $(OPATH)%.o, $(UNIT) $(UNITM))
OBJD = $(patsubst %.c, $(OPATH)db%.o, $(LINE) $(LINEM) $(LEX_SRCS) $(PARSER_SRCS) $(BUILTIN))
LIB = $(addprefix $(LPATH), $(LIBFT))
LIBDB = $(addprefix $(LPATH), $(LIBFTDB))
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
TPATH += unit-tests/
TPATH += unit-tests/interface/
TPATH += unit-tests/lexer/
LINE_PATH += interface/
LINE_PATH += interface/action_keys/
LINE_PATH += interface/action_keys/clipboard/
LINE_PATH += interface/action_keys/movement/
LINE_PATH += interface/core/
LINE_PATH += interface/init/
LINE_PATH += interface/misc/
LINE_PATH += interface/redraw/
LINE_PATH += interface/utils/
LINE_PATH += logging/
LINE_PATH += signals/
LINE_PATH += startup/
LEXER_PATH += lexer/
PARSER_PATH += parser/
BUILTIN_PATH += builtin/
SPATH += $(addprefix srcs/, $(LINE_PATH) $(LEXER_PATH) $(PARSER_PATH) $(BUILTIN_PATH))

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
CFLAGS += -Werror
CFLAGS += $(IFLAGS)
DFLAGS = $(CFLAGS) -fsanitize=address,undefined
LFLAGS = -ltermcap

# ---------------------------------------------------------------------------- #
#									Includes                                   #
# ---------------------------------------------------------------------------- #

INCS += 21sh.h
INCS += log.h
INCS += line_edit.h
INCS += interface_functions.h
INCS += unit.h
INCS += lexer.h
INCS += parser.h
INCS += builtin.h

# ---------------------------------------------------------------------------- #
#									Sources                                    #
# ---------------------------------------------------------------------------- #

#							- - - - - Main - - - - -                           #
UNITM = unit.c
LINEM = main.c

#						- - - - -  Unit-test  - - - - -
UNIT += create_virt_registry.c
UNIT += 00-machine.c
UNIT += clipboard_copy.c
UNIT += clipboard_cut.c
UNIT += clipboard_paste.c
#						- - - - -   Startup   - - - - -

LINE += launch.c
LINE += free.c
LINE += utils.c
LINE += internals.c
LINE += hash.c
LINE += exit.c

#						- - - - -  Debug Log  - - - - -

LINE += debug_logger.c

#						- - - - -  Built-in   - - - - -                        #

BUILTIN += builtin_tools.c
BUILTIN += echo.c

#						- - - - - Line edtion - - - - -                        #

#Signals
LINE += signal_handler.c

#Utilities
LINE += validate_interface.c
LINE += get_prompt_len.c
LINE += input_tools.c
LINE += shift_tools.c
LINE += move_tools.c
LINE += realloc_vector.c
LINE += clean_registry.c
LINE += set_quote.c
LINE += ft_putc.c
LINE += is_eof.c
LINE += print.c

#Misc
LINE += prompt_errors.c

#Redraw
LINE += clean_screen.c
LINE += redraw_prompt.c

#Initialization
LINE += load_interface_config.c
LINE += load_termcap_strings.c

#Core
LINE += cursor.c
LINE += term_mode.c
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

#						   - - - - - Lexer - - - - -                           #

LEX_SRCS += lexer.c
LEX_SRCS += machine_interface.c
LEX_SRCS += states.c
LEX_SRCS += generate_token.c
LEX_SRCS += quotes_states.c
LEX_SRCS += sign_states.c
LEX_SRCS += expansion_states.c
LEX_SRCS += tmp_display.c

#						   - - - - - Parser - - - - -                          #
#
PARSER_SRCS += parser.c
PARSER_SRCS += set_parser_token.c
PARSER_SRCS += generate_graph.c
PARSER_SRCS += parser_debug.c

# ---------------------------------------------------------------------------- #
#									 Rules                                     #
# ---------------------------------------------------------------------------- #

all : $(NAME)

run : $(NAME)
	./$<

debug : $(NAMEDB)
	./$<

test : $(NAMET)
	./$<

#					 - - - - - Normal Compilation - - - - -                    #

$(NAME) : $(CLEAR) $(LIB) $(OPATH) $(OBJS) $(OBJM)
#	@$(shell if ! test -f $(BUILD_NUMBER_FILE); then echo 0 > $(BUILD_NUMBER_FILE); fi)
#	@echo "$(NUMBER_INC)" > $(BUILD_NUMBER_FILE)
	$(LINK) $(OBJS) $(OBJM) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $(LDLIBN) $(LFLAGS) -o $@ 
	$(PRINT) "$(GREEN)$@ is ready $(NC)"

$(OBJM) : $(OPATH)%.o : %.c $(INCS)
	$(COMPILE) $(CFLAGS) $(CPPFLAGS) $< -o $@
	$(PRINT) "$(ONELINE)$(BLUE)Compiling $<                   $(NC)\n"
	
$(OBJS) : $(OPATH)%.o : %.c $(INCS)
	$(COMPILE) $(CFLAGS) $(CPPFLAGS) $< -o $@
	$(PRINT) "$(ONELINE)$(BLUE)Compiling $<                   $(NC)\n"

$(LIB) : FORCE
	$(MAKE) -C $(LPATH)

#					 - - - - Unit test Compilation - - - -                     #

$(NAMET) : $(CLEAR) $(LIB) $(OPATH) $(OBJS) $(OBJT)
	#@$(shell if ! test -f $(BUILD_NUMBER_FILE); then echo 0 > $(BUILD_NUMBER_FILE); fi)
	#@echo "$(NUMBER_INC)" > $(BUILD_NUMBER_FILE)
	$(LINK) $(CFLAGS)  $(LDFLAGS) $(LDLIBN) $(LFLAGS) -fsanitize=address -o  $@ $(OBJT) $(OBJS)
	$(PRINT) "$(GREEN)$@ is ready $(NC)"

$(OBJT) : $(OPATH)%.o : %.c $(INCS)
	$(COMPILE) $(CFLAGS)  $< -o $@
	$(PRINT) "$(ONELINE)$(BLUE)Compiling $<                   $(NC)\n"

#					 - - - - - Debug Compilation - - - - -                     #

$(NAMEDB) : $(CLEAR) $(LIBDB) $(OPATH) $(OBJD)
	$(LINKD) $(OBJD) $(DFLAGS) $(CPPFLAGS) $(LDFLAGS) $(LDLIBD) $(LFLAGS) -o $@ 
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
	$(CLEANUP) $(NAME).dSYM
	$(PRINT) ".o file deleted\n"

fclean : clean
	$(MAKE) -C $(LPATH) fclean
	$(CLEANUP) $(NAME)
	$(CLEANUP) $(NAMEDB)
	$(CLEANUP) $(NAMET)
	$(PRINT) "Executables destroyed\n"

re : fclean all

help :
	@$(PRINT) "Rules available : all, clean,  fclean, re, and help\n"

FORCE:

.PHONY : all 21 21debug lexer lexerdb clean fclean re help FORCE
.SILENT:
