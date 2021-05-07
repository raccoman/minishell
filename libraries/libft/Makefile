
NAME	= libft.a

SRCS	=	$(shell find . -name '*.c')

OBJS	= $(SRCS:.c=.o)

CC		= gcc

RM 		= rm -f

AR		= ar rc

FLAGS	= -Wall -Wextra -Werror

.c.o:
			$(CC) $(FLAGS) -c $< -o $(<:.c=.o)

$(NAME):	$(OBJS)
			$(AR) $(NAME) $(OBJS)
			@ranlib $(NAME)

all:		$(NAME)

clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

norme:
			norminette $(SRCS)

.PHONY:		clean fclean re norme









