CC = cc
FLAGS = -Wall -Wextra -Werror -MMD -MP
SRCS = philo_bonus.c philo_utils_bonus.c philo_routine_bonus.c \
philo_time_bonus.c philo_print_bonus.c philo_error_bonus.c \
philo_process_bonus.c philo_sem_bonus.c
OBJS = $(SRCS:.c=.o)
NAME = philo_bonus

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