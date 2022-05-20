CC = gcc
CFLAGS = -Wall -Werror -Wextra
SANI = -g -fsanitize=address
NAME = philo
INC_PATH = includes/
SRC = main.c init.c utils.c time.c routines.c colors.c
OBJ = $(SRC:.c=.o)

all : $(NAME)


%.o : %.c 
	$(CC) $(CFLAGS) $(SANI) -o $@ -c $< -I $(INC_PATH)

$(OBJ) : $(INC_PATH)$(INCLUDES)

$(NAME) : $(OBJ)
	$(CC) $(SANI) $^ -o philo


COM_COLOR = \033[0;34m
OBJ_COLOR = \033[0;36m
OK_COLOR = \033[0;32m
ERROR_COLOR = \033[0;31m
WARN_COLOR = \033[0;33m
NO_COLOR = \033[m

BLUE_COLOR = \033[1;34m
CYAN_COLOR = \033[1;36m
GREEN_COLOR = \033[1;32m
PURPLE_COLOR = \033[1;35m
GRAY_COLOR = \033[0;37m
DGRAY_COLOR = \033[1;30m
WHITE_COLOR = \033[1;37m



clean : 
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all

test : $(NAME)
	@echo -e "$(OK_COLOR)"
	@echo "" && ./philo && echo ""

.PHONY : all fclean clean re test
