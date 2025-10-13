NAME = philo
CC = cc
FLAGS = -Wall -Werror -Wextra -g3 #-fsanitize=address
RM = rm -rf

SRCS	=	main.c\
			srcs/utils.c\
			srcs/init.c\
			srcs/routine.c\
			srcs/monitor.c\
			srcs/fork.c

GREEN = \033[38;5;114m
ROSE = \033[38;5;218m
BLUE = \033[38;5;153m
NC = \033[0m

OBJS = $(SRCS:.c=.o)

TARGET = $(NAME)

$(NAME): $(LIBRARIES) $(OBJS)
	@echo "$(ROSE)\e[1m┌─────$(NAME)──────────────────────────────────────┐\e"
	@echo "││$(BLUE)	       Compiling $(NAME) 🌀		$(ROSE) │"
	@echo "\e[1m└────────────────────────────────────────────────┘\e"
	@$(CC) $(FLAGS) -o $(NAME) $(OBJS)
	@echo "$(RED)\e[1m┌─────$(NAME)──────────────────────────────────────┐\e"
	@echo "││$(GREEN)	       \e[1mCompilation finished 🌱\e		$(ROSE) │"
	@echo "\e[1m└────────────────────────────────────────────────┘\e"


$(OBJ_DIRS):
	@mkdir -p $@

%.o: %.c
	@$(CC) $(FLAGS) -c $< -o $@

all: $(NAME)

clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(NAME) obj/

re: fclean all

.PHONY: all clean fclean re clear
