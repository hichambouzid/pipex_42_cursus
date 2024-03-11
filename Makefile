NAME = pipex

NAME_BONUS = pipex_bonus

CFLAGS = -Wall -Wextra -Werror 

CFILS = ft_parce_all.c ft_pipex.c     ft_split.c     ft_util_0.c    ft_util_1.c    ft_util_2.c

CFILS_BONUS =  ft_pipex_bonus.c ft_parce_all.c\
			ft_split.c ft_util_0.c ft_util_1.c ft_util_2.c get_next_line.c\
			get_next_line_utils.c

OBJS = $(CFILS:.c=.o)

OBJS_BONUS = $(CFILS_BONUS:.c=.o)

$(NAME):$(OBJS)
	cc  -g3 -fsanitize=address $(OBJS) -o $(NAME)

$(NAME_BONUS):$(OBJS_BONUS)
	cc $(OBJS_BONUS) -o $(NAME_BONUS)

all: $(NAME)

bonus: all $(NAME_BONUS)

clean:
	rm -rf $(OBJS) $(OBJS_BONUS)
fclean: clean
	rm -rf $(NAME) $(NAME_BONUS)

re: fclean all