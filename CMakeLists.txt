cmake_minimum_required(VERSION 3.19)
project(hugeshell C)

set(CMAKE_CXX_STANDARD 89)

include_directories(headers)
include_directories(libraries/libft)

set(LINK_LIBRARIES ${CMAKE_SOURCE_DIR}/libraries)
set(SRCS
		sources/command.c
		sources/configure.c
		sources/env_utils.c
		sources/execute.c
		sources/executor.c
		sources/expand_utils.c
		sources/expander.c
		sources/handle_assign.c
		sources/handle_cd.c
		sources/handle_echo.c
		sources/handle_env.c
		sources/handle_exit.c
		sources/handle_export.c
		sources/handle_keys.c
		sources/handle_pwd.c
		sources/handle_unset.c
		sources/here_doc_utils.c
		sources/history.c
		sources/input.c
		sources/key.c
		sources/more_handle_keys.c
		sources/parse_utils.c
		sources/parser.c
		sources/redirections.c
		sources/safe_split.c
		sources/signals.c
		sources/utils.c sources/wildcards.c)

add_executable(${PROJECT_NAME} main.c ${SRCS})

target_link_libraries(${PROJECT_NAME}
		${LINK_LIBRARIES}/libft/libft.a)
