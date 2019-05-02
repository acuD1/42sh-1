# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/26 18:34:36 by cempassi          #+#    #+#              #
#    Updated: 2019/05/02 20:31:44 by cempassi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ---------------------------------------------------------------------------- #
#								 Build Targets                                 #
# ---------------------------------------------------------------------------- #

NAME = 21sh
NAMEDB = 21shdb
NAMET = unit
LIBFT = libft.a
LIBFTDB = libftdb.a
SRCS = $(LINE) $(LEXER) $(PARSER) $(BUILTIN) $(TOOLS) $(EXPANSION)
OBJM = $(patsubst %.c, $(OPATH)%.o, $(LINEM))
OBJS = $(patsubst %.c, $(OPATH)%.o, $(SRCS))
OBJT = $(patsubst %.c, $(OPATH)%.o, $(UNIT) $(UNITM))
OBJD = $(patsubst %.c, $(OPATH)db%.o, $(LINEM) $(SRCS))
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
LINE_PATH += interface/prompt
LINE_PATH += interface/action_keys/
LINE_PATH += interface/history/
LINE_PATH += interface/action_keys/clipboard/
LINE_PATH += interface/action_keys/movement/
LINE_PATH += interface/core/
LINE_PATH += interface/init/
LINE_PATH += interface/redraw/
LINE_PATH += interface/utils/
LINE_PATH += resolution/
LINE_PATH += logging/
LINE_PATH += signals/
LINE_PATH += ./
LEXER_PATH += lexer/
PARSER_PATH += parser/grammar_parser
PARSER_PATH += parser/application_parser
BUILTIN_PATH += builtin/
BUILTIN_PATH += builtin/cd_blt
BUILTIN_PATH += builtin/echo_blt
BUILTIN_PATH += builtin/env_blt
BUILTIN_PATH += builtin/exit_blt
BUILTIN_PATH += builtin/export_blt
BUILTIN_PATH += builtin/hash_blt
BUILTIN_PATH += builtin/intern_blt
BUILTIN_PATH += builtin/pwd_blt
BUILTIN_PATH += builtin/set_blt
BUILTIN_PATH += builtin/setenv_blt
BUILTIN_PATH += builtin/type_blt
BUILTIN_PATH += builtin/unset_blt
BUILTIN_PATH += builtin/unsetenv_blt
EXPANSION_PATH += expansion/
TOOLS_PATH += tools/
_SPATH = $(LINE_PATH) $(LEXER_PATH) $(PARSER_PATH) $(BUILTIN_PATH) $(TOOLS_PATH) $(EXPANSION_PATH)
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
CFLAGS += -Werror
CFLAGS += $(IFLAGS) 
DFLAGS = $(CFLAGS) -fsanitize=address,undefined,leaks
LFLAGS = -ltermcap

# ---------------------------------------------------------------------------- #
#									Includes                                   #
# ---------------------------------------------------------------------------- #

INCS += 21sh.h
INCS += log.h
INCS += interface_functions.h
INCS += unit.h
INCS += lexer.h
INCS += parser.h
INCS += builtin.h
INCS += resolve.h
INCS += history.h
INCS += define.h
INCS += struct.h
INCS += enum.h

# ---------------------------------------------------------------------------- #
#									Sources                                    #
# ---------------------------------------------------------------------------- #

#							- - - - - Main - - - - -                           #

UNITM = unit.c
LINEM = main.c

#						- - - - -  Unit-test  - - - - -						   #

UNIT += create_virt_registry.c
UNIT += 00-machine.c
UNIT += clipboard_copy.c
UNIT += clipboard_cut.c
UNIT += clipboard_paste.c

#						- - - - -   Startup   - - - - -						   #

LINE += launch.c
LINE += free.c
LINE += utils.c
LINE += internals.c
LINE += routines.c
LINE += read_filedesc.c

#						- - - - -  Debug Log  - - - - -						   #

LINE += debug_logger.c
LINE += print_opt.c

#						- - - - -  Built-in   - - - - -                        #

BUILTIN += blt_tools.c

#CD
BUILTIN += cd_blt.c
BUILTIN += cd_blt_cdpath.c
BUILTIN += cd_blt_additions.c
BUILTIN += cd_blt_simple.c

#ECHO
BUILTIN += echo_blt.c

#ENV
BUILTIN += env_blt.c

#EXIT
BUILTIN += exit_blt.c

#EXPORT
BUILTIN += export_blt.c

#HASH
BUILTIN += hash_blt.c

#INTERN
BUILTIN += intern_blt.c

#PWD
BUILTIN += pwd_blt.c

#SET
BUILTIN += set_blt.c

#SETENV
BUILTIN += setenv_blt.c

#TYPE
BUILTIN += type_blt.c

#UNSET
BUILTIN += unset_blt.c

#UNSETENV
BUILTIN += unsetenv_blt.c

#						- - - - - Line edtion - - - - -                        #

#History
LINE += history.c

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

#Redraw
LINE += clean_screen.c
LINE += redraw_prompt.c

#Initialization
LINE += load_interface_config.c
LINE += load_termcap_strings.c

#Core
LINE += cursor.c
LINE += term_mode.c
LINE += launch_interface.c
LINE += validate_quoting.c
LINE += handle_input_keys.c
LINE += window.c

#Prompt
LINE += prompt.c
LINE += sub_prompt.c

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

LEXER += lexer.c
LEXER += init_lexer.c
LEXER += machine_interface.c
LEXER += states.c
LEXER += generate_token.c
LEXER += quotes_states.c
LEXER += sign_states.c
LEXER += tmp_display.c
LEXER += redirect_states.c

#						   - - - - - Parser - - - - -                          #

#Grammar Parser
PARSER += generate_graph.c
PARSER += ways_graph.c
PARSER += grammar_parser.c
PARSER += parser_debug.c

#Application Parser
PARSER += init_application_parser.c
PARSER += parser_state.c
PARSER += parser_interface.c
PARSER += string_parser.c
PARSER += redirect_parser.c

#						   - - - - Expansion - - - -                           #
EXPANSION += expansion.c
EXPANSION += tilde.c
EXPANSION += variable.c
EXPANSION += quoting.c

#						   - - - -    Tool    - - - -                          #
						   
TOOLS += list_functions.c

#						   - - - - Resolution - - - -                          #

LINE += job_tools.c
LINE += launch_job.c
LINE += launch_process.c
LINE += waitjob.c



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
	$(LINK) $(OBJS) $(OBJM) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $(LDLIBN) $(LFLAGS) -o $@
	$(PRINT) "$(GREEN)$@ is ready\n$(NC)"

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
	$(LINK) $(CFLAGS)  $(LDFLAGS) $(LDLIBN) $(LFLAGS) -fsanitize=address,undefined,leak -o  $@ $(OBJT) $(OBJS)
	$(PRINT) "$(GREEN)$@ is ready\n$(NC)"

$(OBJT) : $(OPATH)%.o : %.c $(INCS)
	$(COMPILE) $(CFLAGS)  $< -o $@
	$(PRINT) "$(ONELINE)$(BLUE)Compiling $<                   $(NC)\n"

#					 - - - - - Debug Compilation - - - - -                     #

$(NAMEDB) : $(CLEAR) $(LIBDB) $(OPATH) $(OBJD)
	$(LINKD) $(OBJD) $(DFLAGS) $(CPPFLAGS) $(LDFLAGS) $(LDLIBD) $(LFLAGS) -o $@
	$(PRINT) "$(GREEN)$@ is ready\n$(NC)"

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
