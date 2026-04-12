# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: brrr1 <brrr1@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/31 06:20:52 by dbouizem          #+#    #+#              #
#    Updated: 2026/04/09 09:12:30 by brrr1            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME  = cub3D

CC = cc
LIBFT_INC = libft/includes
CFLAGS = -Wall -Wextra -Werror -Iinclude -Iminilibx -I$(LIBFT_INC)

OBJ_DIR = obj
MLX_DIR = minilibx
LIBFT_DIR = libft
LIBFT_A = $(LIBFT_DIR)/libft.a

LDFLAGS = $(LIBFT_A) -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz

SRC_CORE = \
	srcs/core/main.c \
	srcs/core/init.c \
	srcs/core/init_mlx.c

SRC_PARSING = \
	srcs/parsing/parse_file.c \
	srcs/parsing/parse_read.c \
	srcs/parsing/parse_split.c \
	srcs/parsing/parse_config.c \
	srcs/parsing/parse_config_headers.c \
	srcs/parsing/parse_config_texture.c \
	srcs/parsing/parse_config_color.c \
	srcs/parsing/parse_config_utils.c \
	srcs/validation/validate_map.c \
	srcs/validation/validate_map_player.c \
	srcs/validation/validate_map_chars.c \
	srcs/validation/validate_map_closed.c \
	srcs/validation/validate_map_closed_bfs.c \
	srcs/validation/validate_map_closed_utils.c \
	srcs/validation/init_player.c

SRC_RENDER = \
	srcs/render/draw_frame.c \
	srcs/render/render_utils.c \
	srcs/render/raycast_init.c \
	srcs/render/raycast_trace.c \
	srcs/render/raycast_draw.c

SRC_INPUT = \
	srcs/input/keyboard.c \
	srcs/input/movement.c \
	srcs/input/rotation.c

SRC_TOOLS = \
	srcs/tools/error.c \
	srcs/tools/memory.c

SRCS = $(SRC_CORE) $(SRC_PARSING) $(SRC_RENDER) $(SRC_INPUT) $(SRC_TOOLS)

OBJS = $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRCS))

RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
CYAN = \033[1;36m
RESET = \033[0m

all: $(NAME)

$(NAME): $(LIBFT_A) $(OBJS)
	@$(MAKE) -C $(MLX_DIR) --no-print-directory > /dev/null 2>&1
	@echo "$(CYAN)Linking... $(NAME)$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS)
	@echo "$(GREEN)✓ $(NAME) compiled successfully!$(RESET)"

$(LIBFT_A):
	@echo "$(YELLOW)Building libft...$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory > /dev/null 2>&1
	@echo "$(GREEN)✓ libft ready!$(RESET)"

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

bonus: all

clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory > /dev/null 2>&1

fclean: clean
	@echo "$(RED)Cleaning...$(RESET)"
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory > /dev/null 2>&1
	@$(MAKE) -C $(MLX_DIR) clean --no-print-directory > /dev/null 2>&1
	@echo "$(GREEN)✓ All cleaned.$(RESET)"

re: fclean
	@$(MAKE) all --no-print-directory

.PHONY: all bonus clean fclean re
