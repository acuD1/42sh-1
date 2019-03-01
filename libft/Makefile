# ---------- #
# Debug mode #
# ---------- #

DEBUG = no

# --------- #
# Directory #
# --------- #

SRCDIR = srcs/
OBJDIR = objs/
INCDIR = includes/
LIBDIR = libs/

# ------------------ #
# Compiler and flags #
# ------------------ #

CC = clang
ifeq ($(DEBUG), yes)
	CFLAGS = -Wall -Wextra -fsanitize=address
	LDFLAGS =
else
	CFLAGS = -Wall -Wextra -Werror
	LDFLAGS =
endif
CPPFLAGS = -I$(INCDIR)

# --------------- #
# Differents name #
# --------------- #

NAME = $(LIBDIR)libft.a

SRCS_NAMES = $(shell ls -1 $(SRCDIR))
OBJS_NAMES = $(SRCS_NAMES:.c=.o)
HEADER_NAMES = $(shell ls -1 $(INCDIR))

SRC = $(addprefix $(SRCDIR), $(SRCS_NAMES))
OBJ = $(addprefix $(OBJDIR), $(OBJS_NAMES))
HEADER = $(addprefix $(INCDIR), $(HEADER_NAMES))

# ----------------- #
# Command variables #
# ----------------- #

AR = ar
ARFLAGS = rc
SORT = ranlib
CREATE = mkdir -p
DEL = /bin/rm -rf
PRINT = echo
PHONY = all clean fclean re help

# ----- #
# Rules #
# ----- #

all : $(NAME)

ifeq ($(DEBUG), yes)
	@$(PRINT) ""
else
	@$(PRINT) ""
endif

$(NAME) : $(OBJ)
	@$(CREATE) $(LIBDIR)
	@$(AR) $(ARFLAGS) $(NAME) $(OBJ)
	@$(SORT) $(NAME)
	@$(PRINT) "Libft.a built"

$(OBJDIR)%.o : $(SRCDIR)%.c $(HEADER)
	@$(CREATE) $(OBJDIR)
	@$(CC) -o $@ -c $< $(CFLAGS) $(CPPFLAGS)

clean :
	@$(DEL) $(OBJDIR)

fclean : clean
	@$(DEL) $(LIBDIR)
	@$(PRINT) "Libft.a destroyed"

re : fclean all

help :
	@$(PRINT) "Rules available : all, clean, fclean, re and help"

.PHONY : $(PHONY)
