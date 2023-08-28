NAME = philo
CC = cc -g -Wall -Wextra -Werror #-fsanitize=thread

SRCS = philo_main.c philo_util.c \
		philo_life.c philo_input.c philo_exe.c
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