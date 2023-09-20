NAME = cub3D

PATH_MLX = minilibx-linux

SRCS = srcs/main.c \
			srcs/win_init.c \
			srcs/ft_utils_1.c \
			srcs/ft_utils_2.c \
			srcs/ft_utils_3.c \
			srcs/get_next_line.c \
			srcs/get_next_line_utils.c \
			srcs/parsing.c \
			srcs/error.c \
			srcs/parsing_map.c \
			srcs/parsing_map_2.c \
			srcs/input.c \
			srcs/player_movement.c \
			srcs/raycasting.c \
			srcs/raycasting_2.c \

OBJS = srcs/main.o \
			srcs/win_init.o \
			srcs/ft_utils_1.o \
			srcs/ft_utils_2.o \
			srcs/ft_utils_3.o \
			srcs/get_next_line.o \
			srcs/get_next_line_utils.o \
			srcs/parsing.o \
			srcs/error.o \
			srcs/parsing_map.o \
			srcs/parsing_map_2.o \
			srcs/input.o \
			srcs/player_movement.o \
			srcs/raycasting.o \
			srcs/raycasting_2.o \

INCLUDES = -I/includes/cube.h

CFLAGS = -Wall -Werror -Wextra -fPIE

GCC = gcc 

LIB =  minilibx-linux/libmlx_Linux.a -I./usr/include -L minilibx-linux -Lmlx_linux -Imlx_linux -lXext -lX11 -lm

RM = rm -f

all: ${NAME}

${NAME}: ${OBJS}
		make -C $(PATH_MLX)
		${GCC} ${CFLAGS} ${INCLUDES} ${OBJS} ${LIB} -o ${NAME}

clean: 
	make -C $(PATH_MLX) clean
	${RM} ${OBJS}

fclean: clean
	make -C $(PATH_MLX) clean
	${RM} ${NAME}

re: fclean all

.PHONY: clean fclean re