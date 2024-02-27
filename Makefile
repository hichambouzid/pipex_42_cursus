NAME = pipex

CFLAGS = -Wall -Wextra -Werror

CFILS = ft_pipex.c  ft_split.c  ft_util_0.c ft_util_1.c ft_util_2.c

OBJS = $(CFILS:.c=.o)

$(NAME):$(OBJS)
	cc -fsanitize=address -g3 $(OBJS) -o $(NAME)
all: $(NAME)

clean:
	rm -rf $(OBJS)
fclean: clean
	rm -rf $(NAME)

re: fclean all