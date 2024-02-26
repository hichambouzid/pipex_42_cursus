NAME = pipex

CFLAGS = -Wall -Wextra -Werror

CFILS =

OBJS = $(CFILS:.c=.o)
$(NAME):$(OBJS)

all: $(NAME)

clean:

fclean:

re: