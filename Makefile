# ---------- #
# Debug mode #
# ---------- #

DEBUG = yes

# --------- #
# Directory #
# --------- #

LIBDIR = libft/
PATHLIBDIR = libft/
SRCDIR = srcs/
OBJDIR = objs/
INCDIR = includes/
INCLIBDIR = libft/includes/

VPATH = objs:srcs:srcs/startup:srcs/logging:srcs/signals:srcs/misc:srcs/interface:srcs/exec:srcs/interface/utils:srcs/interface/core:srcs/interface/init:srcs/interface/misc:srcs/interface/history:srcs/interface/misc

# ------------------ #
# Compiler and flags #
# ------------------ #

CC = gcc
ifeq ($(DEBUG), yes)
	CFLAGS = -Wall -Wextra -fsanitize=address #-Werror
else
	CFLAGS = -Wall -Wextra -Werror
endif
CPPFLAGS = -I $(INCDIR) -I $(INCLIBDIR)
LDLIBS = -lft
LDFLAGS = -L $(PATHLIBDIR)

LFLAGS = -ltermcap

# --------------- #
# Different names #
# --------------- #

NAME = 21sh

SRCS_NAMES = 21sh.c argument_parser.c environment_parser.c startup_initialisation.c workspace.c\
			 file_logger.c debug_logger.c vector_tools.c\
			 termcap_strings.c load_interface_config.c keymap_handler.c\
			 init_special_ak.c init_ctrl_ak.c init_arrow_ak.c init_clipboard.c\
			 action_keys.c execute_arrow_ak.c execute_ctrl_ak.c execute_special_ak.c\
			 signal_handler.c prompt.c redraw_prompt.c sub_shell.c validate_input.c\
			 prompt_errors.c handle_input_keys.c init_ak_keycodes.c command_history.c cleanup.c


OBJS_NAMES = $(SRCS_NAMES:.c=.o)
HEADERS_NAMES = 21sh.h line_edit.h log.h history.h startup.h
LIBS_NAMES = libft.a

OBJ = $(addprefix $(OBJDIR), $(OBJS_NAMES))
HEADERS = $(addprefix $(INCDIR), $(HEADERS_NAMES))
LIBS = $(addprefix $(PATHLIBDIR), $(LIBS_NAMES))

# ----------------- #
# Command variables #
# ----------------- #

CREATE = mkdir -p
DEL = /bin/rm -rf
PRINT = echo
PHONY = all clean cleans fclean re libs cleanlibs fcleanlibs help

# ----- #
# Rules #
# ----- #

all : libs $(NAME)

ifeq ($(DEBUG), yes)
	@$(PRINT) "Debug mode : on\n"
else
	@$(PRINT) "Debug mode : off\n"
endif

$(NAME) : $(OBJS_NAMES) $(LIBS)
	@$(CC) -o $@ $(OBJ) $(LDFLAGS) $(LDLIBS) $(LFLAGS) $(CFLAGS) $(CPPFLAGS)
	@$(PRINT) "Executable built"

libs :
	@$(MAKE) -C $(LIBDIR)

%.o : %.c $(HEADER)
	@$(CREATE) $(OBJDIR)
	@$(CC) -o $(OBJDIR)$@ -c $< $(CFLAGS) $(CPPFLAGS)
	@$(PRINT) ".o created"

clean : cleanlibs
	@$(DEL) $(OBJDIR)
	@$(PRINT) ".o file deleted"

cleans : 
	@$(DEL) $(OBJDIR)
	@$(PRINT) ".o file deleted"

fclean : cleans fcleanlibs
	@$(DEL) $(NAME)
	@$(PRINT) "Executable destroyed"

cleanlibs :
	@$(MAKE) -C $(LIBDIR) clean

fcleanlibs :
	@$(MAKE) -C $(LIBDIR) fclean

re : fclean all

help :
	@$(PRINT) "Rules available : all, clean, cleans, fclean, re, libs, cleanlibs, fcleanlibs and help"

.PHONY : $(PHONY)
