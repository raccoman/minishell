#Name
NAME =			minishell
DEBUG =			debug

#Compiler
CC = 			gcc
CFLAGS = 		-Wall -Wextra -Werror
LIBRARIES =		$(LIBFT_DIR)/$(LIBFT)
CFLAG = 		-c
OFLAG =			-o
IFLAG =			-I

#Make
MAKE = 			make -s -C
MAKE_CLEAN = 	make clean -s -C
MAKE_FCLEAN = 	make fclean -s -C

FILES =	command.c \
		configure.c \
		env_utils.c \
		execute.c \
		executor.c \
		expand_utils.c \
		expander.c \
		handle_assign.c \
		handle_cd.c \
		handle_echo.c \
		handle_env.c \
		handle_exit.c \
		handle_export.c \
		handle_keys.c \
		handle_pwd.c \
		handle_unset.c \
		here_doc_utils.c \
		history.c \
		input.c \
		key.c \
		more_handle_keys.c \
		parse_utils.c \
		parser.c \
		redirections.c \
		safe_split.c \
		signals.c \
		utils.c \
		wildcards.c \
		wildcards_utils.c \
		priorities.c

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
LIBFT =	libft.a

SRCS =	$(foreach FILE, $(FILES), $(shell find $(SOURCES_DIR) -name $(FILE)))

MAIN = main.c

#Objs
OBJS =	$(patsubst $(SOURCES_DIR)/%, $(OBJECTS_DIR)/%, $(SRCS:.c=.o))

$(OBJECTS_DIR)/%.o: $(SOURCES_DIR)/%.c
	@$(MKDIR) $(@D)
	@$(CC) $(CFLAG) $(CFLAGS) $(IFLAG)$(HEADERS_DIR) $(OFLAG) $@ $<
	@printf "\e[0;33mCompiling... %s -> %-33.33s\r" $< $@

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	@printf "\n\e[0;33m"
	$(CC) $(CFLAGS) $(OBJS) $(IFLAG)$(HEADERS_DIR) -L$(LIBFT_DIR) -lft $(MAIN) $(OFLAG) $(NAME)
	@printf "\e[0;32mDone!\n\e[0m"

$(LIBFT):
	@$(MAKE) $(LIBFT_DIR)

norme:
	@$(NORM) $(MAIN) $(SRCS)
	@$(NORM) $(shell find $(HEADERS_DIR) -name *.h)

clean:
	@printf "\e[0;31m"
	$(RM) $(OBJECTS_DIR)
	@printf "\e[0m"
	@$(RM) $(DEBUG).dSYM/
	@$(MAKE_CLEAN) $(LIBFT_DIR)

fclean: clean
	@printf "\e[0;31m"
	$(RM) $(NAME)
	@printf "\e[0m"
	@$(RM) $(DEBUG)
	@$(MAKE_FCLEAN) $(LIBFT_DIR)

re: fclean all clean

debug: $(LIBFT) $(SRCS)
	@$(CC) -g $(MAIN) $(SRCS) $(IFLAG)$(HEADERS_DIR) -L$(LIBFT_DIR) -lft $(OFLAG) $(DEBUG)
	@lldb debug

run: re
	@./minishell

.PHONY: all norminette clean fclean re debug run