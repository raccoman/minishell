cmake_minimum_required(VERSION 3.19)
project(hugeshell C)

set(CMAKE_CXX_STANDARD 89)

include_directories(headers)
include_directories(libraries/libft)

set(LINK_LIBRARIES ${CMAKE_SOURCE_DIR}/libraries)
set(SRCS
		sources/minishell.c
		sources/parser.c
		sources/key.c)

add_executable(${PROJECT_NAME} main.c ${SRCS})

target_link_libraries(${PROJECT_NAME}
		${LINK_LIBRARIES}/libft/libft.a)
