# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: brrr1 <brrr1@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/31 06:20:52 by dbouizem          #+#    #+#              #
#    Updated: 2026/04/02 15:41:38 by brrr1            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME  = cub3D
BONUS_NAME = cub3D_bonus

CC = cc
LIBFT_INC = libft/includes
CFLAGS = -Wall -Wextra -Werror -Iinclude -Iminilibx -I$(LIBFT_INC)
OBJ_DIR = obj
MLX_DIR = minilibx
LIBFT_DIR = libft
LIBFT_A = $(LIBFT_DIR)/libft.a
HEADERS = $(wildcard include/*.h) $(wildcard $(LIBFT_INC)/*.h)

LDFLAGS = $(LIBFT_A) -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz

SRC_CORE = \
		srcs/core/main.c \
		srcs/core/init_app.c \
		srcs/core/init_mlx.c \
		srcs/core/shutdown.c \
		srcs/core/window_resize.c

SRC_PARSING = \
	srcs/parsing/parse_file.c \
	srcs/parsing/parse_read.c \
	srcs/parsing/parse_split.c \
	srcs/parsing/parse_map.c \
	srcs/parsing/parse_config.c \
	srcs/parsing/parse_textures.c \
	srcs/parsing/parse_colors.c \
	srcs/parsing/parse_utils.c \
	srcs/validation/validate_map.c \
	srcs/validation/validate_map_player.c \
	srcs/validation/validate_map_chars.c \
	srcs/validation/validate_map_closed.c \
	srcs/validation/validate_closed_setup.c \
	srcs/validation/validate_bfs.c

SRC_RENDER = \
	srcs/render/render_frame.c \
	srcs/render/draw_vignette.c \
	srcs/render/raycast.c \
	srcs/render/raycast_draw.c

SRC_INPUT = \
	srcs/input/input_keys.c \
	srcs/input/input_mouse.c \
	srcs/input/input_update.c \
	srcs/input/move_collision.c \
	srcs/input/move_player.c \
	srcs/input/rotation.c

SRC_TOOLS = \
	srcs/tools/utils.c

BONUS_NOOP_SRCS = \
	srcs_bonus/noop/retro_noop.c \
	srcs_bonus/noop/shading_noop.c \
	srcs_bonus/noop/hud_noop.c \
	srcs_bonus/noop/levels_map_noop.c \
	srcs_bonus/noop/pickups_noop.c \
	srcs_bonus/noop/sprites_noop.c \
	srcs_bonus/noop/sprites_query_noop.c \
	srcs_bonus/noop/walls_noop.c \
	srcs_bonus/noop/doors_api_noop.c \
	srcs_bonus/noop/doors_logic_noop.c \
	srcs_bonus/noop/doors_query_noop.c

MANDATORY_SRCS = $(SRC_CORE) $(SRC_PARSING) $(SRC_RENDER) $(SRC_INPUT) $(SRC_TOOLS) $(BONUS_NOOP_SRCS)

BONUS_SRCS = \
	srcs_bonus/retro/api.c \
	srcs_bonus/retro/image.c \
	srcs_bonus/retro/display.c \
	srcs_bonus/retro/minimap.c \
	srcs_bonus/retro/minimap_pixels.c \
	srcs_bonus/retro/shading.c \
	srcs_bonus/retro/flat_shading.c \
	srcs_bonus/retro/walls_rules.c \
	srcs_bonus/retro/walls_core.c \
	srcs_bonus/retro/walls_anim_pick.c \
	srcs_bonus/retro/walls_symbol_pick.c \
	srcs_bonus/retro/walls_io.c \
	srcs_bonus/retro/walls_anim_io.c \
	srcs_bonus/retro/walls_paths.c \
	srcs_bonus/retro/walls_destroy.c \
	srcs_bonus/retro/walls_symbol_io.c \
	srcs_bonus/levels/levels_api.c \
	srcs_bonus/levels/levels_current.c \
	srcs_bonus/levels/levels_reload.c \
	srcs_bonus/levels/levels_textures.c \
	srcs_bonus/levels/levels_transfer.c \
	srcs_bonus/pickups/pickups_effects.c \
	srcs_bonus/pickups/pickups_api.c \
	srcs_bonus/pickups/pickups_sprites.c \
	srcs_bonus/pickups/pickups_update.c \
	srcs_bonus/hud/hud_assets.c \
	srcs_bonus/hud/hud_blit.c \
	srcs_bonus/hud/hud_colors.c \
	srcs_bonus/hud/hud_draw.c \
	srcs_bonus/hud/hud_face_paths.c \
	srcs_bonus/hud/hud_fire.c \
	srcs_bonus/hud/hud_frames.c \
	srcs_bonus/hud/hud_glyphs.c \
	srcs_bonus/hud/hud_level.c \
	srcs_bonus/hud/hud_overlay.c \
	srcs_bonus/hud/hud_panels.c \
	srcs_bonus/hud/hud_scaled.c \
	srcs_bonus/hud/hud_state.c \
	srcs_bonus/hud/hud_status.c \
	srcs_bonus/hud/hud_text.c \
	srcs_bonus/hud/hud_weapon_slot.c \
	srcs_bonus/sprites/sprites_api.c \
	srcs_bonus/sprites/sprites_alloc.c \
	srcs_bonus/sprites/sprites_assets.c \
	srcs_bonus/sprites/sprites_bounds.c \
	srcs_bonus/sprites/sprites_depth.c \
	srcs_bonus/sprites/sprites_helpers.c \
	srcs_bonus/sprites/sprites_space.c \
	srcs_bonus/sprites/sprites_sort.c \
	srcs_bonus/sprites/sprites_render.c \
	srcs_bonus/sprites/sprites_setup.c \
	srcs_bonus/sprites/sprites_shadow.c \
	srcs_bonus/sprites/sprites_shutdown.c \
	srcs_bonus/doors/doors_api.c \
	srcs_bonus/doors/doors_logic.c \
	srcs_bonus/doors/doors_utils.c \
	srcs_bonus/doors/doors_query.c

BONUS_REPLACE_SRCS = \
	$(BONUS_NOOP_SRCS) \
	srcs/render/raycast_shading.c

SRCS = $(MANDATORY_SRCS)

OBJS = $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRCS))

RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
CYAN = \033[1;36m
RESET = \033[0m

all: $(NAME)

$(NAME): $(LIBFT_A) $(OBJS)
	@env -u MAKEFLAGS -u MAKEOVERRIDES -u MFLAGS -u CFLAGS -u CPPFLAGS -u LDFLAGS \
		$(MAKE) -C $(MLX_DIR) --no-print-directory > /dev/null 2>&1
	@echo "$(CYAN)Linking... $(NAME)$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS)
	@echo "$(GREEN)✓ $(NAME) compiled successfully!$(RESET)"

$(LIBFT_A):
	@echo "$(YELLOW)Building libft...$(RESET)"
	@env -u MAKEFLAGS -u MAKEOVERRIDES -u MFLAGS -u CFLAGS -u CPPFLAGS -u LDFLAGS \
		$(MAKE) -C $(LIBFT_DIR) --no-print-directory > /dev/null 2>&1
	@echo "$(GREEN)✓ libft ready!$(RESET)"

$(OBJ_DIR)/%.o: %.c $(HEADERS)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

bonus:
	@$(MAKE) NAME="$(BONUS_NAME)" SRCS="$(filter-out $(BONUS_REPLACE_SRCS),$(MANDATORY_SRCS)) $(BONUS_SRCS)" OBJ_DIR=obj_bonus CFLAGS="$(CFLAGS) -DBONUS" all --no-print-directory

clean:
	@rm -rf $(OBJ_DIR) obj_asan obj_bonus
	@$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory > /dev/null 2>&1

fclean: clean
	@echo "$(RED)Cleaning...$(RESET)"
	@rm -f $(NAME) $(BONUS_NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory > /dev/null 2>&1
	@$(MAKE) -C $(MLX_DIR) clean --no-print-directory > /dev/null 2>&1
	@echo "$(GREEN)✓ All cleaned.$(RESET)"

re: fclean
	@$(MAKE) all --no-print-directory

rebonus: fclean
	@$(MAKE) bonus --no-print-directory

test: all
	@./tests/run.sh

test_bonus: bonus
	@./tests/run_bonus.sh ./$(BONUS_NAME)

.PHONY: all bonus clean fclean re rebonus test test_bonus
