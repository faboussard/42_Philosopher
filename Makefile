
NAME			=	philo

#-------------  VPATH  ---------------#

vpath %c philo srcs

# --------------- FILES --------------- #

LIST_SRCS		=  main exit init

LIST_HEADERS	= philo

# ------------ DIRECTORIES ------------ #

DIR_BUILD		=	.build/
SUPP_LEAK_DIR := $(shell pwd)
SUBDIRS := .build/philo

DIR_HEADERS		=	philo/includes/

# ------------- SHORTCUTS ------------- #

OBJS            = $(addprefix $(DIR_BUILD), $(addsuffix .o, $(LIST_SRCS)))
HEADERS			= $(addprefix $(DIR_HEADERS), $(addsuffix .h, $(LIST_HEADERS)))
DEPS            = ${OBJS:.o=.d}
INCLUDES        = -I $(DIR_HEADERS)

# ------------ COMPILATION ------------ #

CC				=	cc

CFLAGS			=	-Wall -Wextra -Werror -pthread #-fsanitize=address -fsanitize=thread #-fPIE

DEPS_FLAGS		=	-MMD -MP

# -------------  COMMANDS ------------- #

MKDIR			=	mkdir -p

#***********************************  RULES  **********************************#

all:			 $(NAME)

# ---------- VARIABLES RULES ---------- #

$(NAME): $(OBJS) Makefile
	$(CC) $(CFLAGS) $(OBJS) $(INCLUDES) -o $(NAME)

# ---------- COMPILED RULES ----------- #

$(DIR_BUILD)%.o: %.c Makefile | $(SUBDIRS)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

#---------- CREATE REPO OBJS ---------#

$(SUBDIRS): $(DIR_BUILD)
	@echo "Création du sous-répertoire $@"
	@$(MKDIR) $@

$(DIR_BUILD):
	@echo "Création du répertoire $(DIR_BUILD)"
	@$(MKDIR) $(DIR_BUILD)


debug: clean
	$(MAKE) CFLAGS="-g"

clean:
			rm -rf $(DIR_BUILD)

fclean: clean
			if [ -f $(NAME) ]; then rm -f $(NAME); fi

re:				fclean all

.PHONY: all clean fclean re

-include $(DEPS)