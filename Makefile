#Name
NAME =			minishell
DEBUG =			debug

#Compiler
CC = 			gcc
CFLAGS = 		#-Wall -Wextra -Werror
LIBRARIES =		$(LIBFT_DIR)/$(LIBFT)
CFLAG = 		-c
OFLAG =			-o
IFLAG =			-I

#Make
MAKE = 			make -s -C
MAKE_CLEAN = 	make clean -s -C
MAKE_FCLEAN = 	make fclean -s -C

#Norm
NORM =			norminette

#Shell
MKDIR =			mkdir -p
CP =			cp
RM =			rm -rf

#Directories
SOURCES_DIR = 	./sources
OBJECTS_DIR =  	./objects
HEADERS_DIR = 	./headers
LIBRARIES_DIR = ./libraries

LIBFT_DIR = 	./libraries/libft

#Libs
LIBFT = 	libft.a

#Srcs
SRCS =			$(shell find $(SOURCES_DIR) -name '*.c')

#Objs
OBJS =			$(patsubst $(SOURCES_DIR)/%, $(OBJECTS_DIR)/%, $(SRCS:.c=.o))

$(OBJECTS_DIR)/%.o: $(SOURCES_DIR)/%.c
	@$(MKDIR) $(@D)
	@$(CC) $(IFLAG) $(HEADERS_DIR) $(IFLAG) $(LIBRARIES_DIR) $(CFLAG) $(OFLAG) $@ $<

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBRARIES) main.c $(OFLAG) $(NAME)
	@echo "Done!"

$(LIBFT):
	@$(MAKE) $(LIBFT_DIR)

norminette:
	@$(NORM) $(shell find $(SOURCES_DIR) -name *.c)
	@$(NORM) $(shell find $(HEADERS_DIR) -name *.h)


clean:
	@$(RM) $(OBJECTS_DIR)
	@$(RM) $(DEBUG).dSYM/
	@$(MAKE_CLEAN) $(LIBFT_DIR)

fclean: clean
	@$(RM) $(NAME) $(DEBUG)
	@$(MAKE_FCLEAN) $(LIBFT_DIR)

re: fclean all clean

debug: $(LIBFT) $(SRCS)
	@$(CC) -g main.c $(SRCS) $(IFLAG) $(HEADERS_DIR) -L$(LIBFT_DIR) -lft $(OFLAG) $(DEBUG)
	@lldb debug

run: re
	@./minishell

.PHONY: all norminette clean fclean re debug run