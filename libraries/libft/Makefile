
NAME	= libft.a

FILES	=	ft_append.c \
			ft_append_element.c \
			ft_atoi.c \
			ft_contains.c \
			ft_fflush.c \
			ft_free2D.c \
			ft_insert.c \
			ft_is_num.c \
			ft_itoa.c \
			ft_lstadd_back.c \
			ft_lstadd_front.c \
			ft_lstclear.c \
			ft_lstlast.c \
			ft_lstnew.c \
			ft_lstrmv_if.c \
			ft_lstsize.c \
			ft_memcpy.c \
			ft_onlythischar.c \
			ft_remove_at.c \
			ft_split.c \
			ft_strcmp.c \
			ft_strdup.c \
			ft_strjoin.c \
			ft_strlcpy.c \
			ft_strlen.c \
			ft_strjoin2D.c \
			ft_count.c \
			ft_find.c \
			ft_replace.c

SRCS =	$(foreach FILE, $(FILES), $(shell find . -name $(FILE)))

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









