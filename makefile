NAME = philo
CC = cc -g -Wall -Wextra -Werror

SRCS_DIR = ./srcs
SRCS = philo_main.c
OBJS = $(addprefix $(SRCS_DIR)/, $(SRCS:.c=.o))

BONUS_DIR = ./bonus
SRCS_BONUS = 
OBJS_BONUS = $(addprefix $(BONUS_DIR)/, $(SRCS_BONUS:.c=.o))

ifdef BONUS
	FIXED_OBJS = $(OBJS_BONUS)
else
	FIXED_OBJS = $(OBJS)
endif

all : $(NAME)

$(NAME) : $(FIXED_OBJS)
	$(CC) $(FIXED_OBJS) -o $(NAME)

clean :
	rm -rf $(OBJS) $(OBJS_BoNUS)

fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY : all clean fclean re bonus