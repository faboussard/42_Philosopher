NAME	= philo
CC		= cc
CFLAGS	= -Werror -Wall -Wextra -pthread -g #-fsanitize=address

SRC_PATH = sources/
OBJ_PATH = objects/

SRC		=	main.c \
			init.c \
			error.c \
			utils.c \
		    lib1.c \
		    lib2.c \
		    free.c \
		    thread.c

SRCS	= $(addprefix $(SRC_PATH), $(SRC))
OBJ		= $(SRC:.c=.o)
OBJS	= $(addprefix $(OBJ_PATH), $(OBJ))

INC		= -I ./includes/

all: $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c includes/philo.h
	@mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) -c $< -o $@ $(INC)

$(NAME): includes/ $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

debug: clean
	$(MAKE) CFLAGS="-g"

clean:
	rm -rf $(OBJ_PATH)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all re clean fclean