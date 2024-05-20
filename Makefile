CC = cc
FLAGS = -Wall -Wextra -Werror -MMD -MP -g3
SRCS = philo.c philo_utils.c
OBJS = $(SRCS:.c=.o)
NAME = philo

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME)

%.o : %.c
	$(CC) $(FLAGS) -c $< -o $@

clean : 
	rm -rf $(OBJS)
	rm -rf $(SRCS:.c=.d)
	rm -rf .mandatory

fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY: all clean re fclean