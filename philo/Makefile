CC = cc
FLAGS = -Wall -Wextra -Werror -MMD -MP
SRCS = philo.c philo_utils.c philo_routine.c philo_time.c philo_print.c \
		philo_error.c philo_mutex.c
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

fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY: all clean re fclean