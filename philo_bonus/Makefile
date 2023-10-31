NAME = philo_bonus
CC = cc -g -Wall -Wextra -Werror

SRCS = philo_bonus_main.c philo_bonus_input.c \
		philo_bonus_exe.c philo_bonus_func.c \
		philo_bonus_util.c

OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(OBJS) -o $(NAME)

clean :
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY : all clean fclean re