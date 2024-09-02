# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: okrahl@student.42.fr)              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/10 18:18:03 by okrahl            #+#    #+#              #
#    Updated: 2024/05/15 15:30:05 by okrahl           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# COLORS FOR PRINTING
GREEN = \033[0;32m
RESET = \033[0m

# DIRECTORIES
OBJ_DIR = obj
SRC_DIR = src
INCL_DIR = incl
LIBFT_DIR = libraries/libft
MLX_DIR = libraries/mlx

# EXECUTABLE NAME
NAME = cubed3D

# SOURCE FILES
SRCS = 	main.c \
		initialize_game.c \
		helper.c \
		helper2.c \
		helper3.c \
		close_game.c \
		initialize_data.c \
		initialize_player.c \
		draw_minimap.c \
		helper_draw_minimap.c \
		raycaster.c \
		update_game.c \
		update_player.c \
		3D_visualizer.c \
		3D_visualizer2.c \
		get_image.c \
		args_check.c \
		cubfile_check.c \
		utils.c \
		utils2.c \
		free_assets.c \
		free_data.c \
		prepare_assets.c \
		prepare_assets2.c \
		prepare_assets3.c \
		alloc_memory.c \
		settings.c \
		ray_utils.c \
		backtrack.c \
		wall_checks.c
		

# OBJECT FILES
OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

# COMPILER
CC = gcc

# COMPILATION FLAGS
CFLAGS = -Wall -Wextra -Werror -I$(INCL_DIR) -Imlx_linux -I$(LIBFT_DIR) -g

# LINKER FLAGS
LDFLAGS = -Lmlx_linux -lmlx -L/usr/lib -lXext -lX11 -lm -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx

# COMMANDS
RM = rm -f
MKDIR = mkdir -p

# LIBRARIES
LIBFT = $(LIBFT_DIR)/libft.a
MLX = $(MLX_DIR)/libmlx.a

# RULES
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(MKDIR) $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

all : $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(MLX):
	@if [ ! -f $(MLX) ]; then \
		echo "Installing libmlx.a..."; \
		$(MAKE) -C $(MLX_DIR); \
	fi

$(NAME) : $(LIBFT) $(MLX) $(OBJS)
	@$(CC) $(OBJS) $(LDFLAGS) -o $(NAME)
	@echo "$(GREEN)./$(NAME) is ready!$(RESET)"

fclean : clean
	@$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

clean :
	@$(RM) -r $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean

re : fclean all

.PHONY : all clean fclean re