NAME = ./rainbowcat

SRC =	srcs/rainbowcat.c

OBJ = $(SRC:.c=.o)

FLAGS = -Wall -Wextra -Werror

INC= -I./includes

$(NAME): $(LIB)
	@gcc $(FLAGS) $(INC) $(SRC) -o $(NAME) -lm;
	@echo compiling rainbowcat

all: $(NAME)

clean:
	@rm -rf $(OBJ)
	@echo deleting binary files

fclean: clean
	@rm -rf $(NAME)
	@echo deleting rainbowcat

re: fclean all

.PHONY : all, re, clean, fclean
