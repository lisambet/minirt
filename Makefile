# Compilation
CC					=	cc
MLX_FLAGS			=	-L minilibx-linux -lmlx -lXext -lX11 -lm
CFLAGS				=	-Wall -Wextra -Werror -g $(INCLUDES) -MP -MMD

# Names
NAME				=	miniRT

# Sources & Includes
SRCS				= 	srcs/main.c \
						srcs/init.c \
						srcs/exec/cylinder.c \
						srcs/exec/events.c \
						srcs/exec/hit_cylinder.c \
						srcs/exec/light.c \
						srcs/exec/objects.c \
						srcs/exec/ray.c \
						srcs/exec/shadow.c \
						srcs/parsing/file_management.c \
						srcs/parsing/parsing_checks.c \
						srcs/parsing/parsing_objects.c \
						srcs/parsing/parsing_render.c \
						srcs/parsing/parsing.c \
						srcs/utils/cleanup.c \
						srcs/utils/cylinder_utils.c \
						srcs/utils/errors.c \
						srcs/utils/free.c \
						srcs/utils/get_normal.c \
						srcs/utils/plane_utils.c \
						srcs/utils/sphere_utils.c \
						srcs/utils/vec1.c \
						srcs/utils/vec2.c \
						srcs/utils/vec3.c

OBJ_FOLDER			=	objs
LIB					=	libft/libft.a
INCLUDES			=	-I minilibx-linux -I includes -I libft

# Objects
OBJS				=	$(patsubst srcs/%, $(OBJ_FOLDER)/%, $(SRCS:.c=.o))
DEPS				=	$(patsubst srcs/%, $(OBJ_FOLDER)/%, $(SRCS:.c=.d))
BOBJS				=	$(patsubst srcs/%, $(OBJ_FOLDER)/%, $(BSRCS:.c=.o))
BDEPS				=	$(patsubst srcs/%, $(OBJ_FOLDER)/%, $(BSRCS:.c=.d))

# Custom Makefile Flags
MAKEFLAGS			+=	--no-print-directory --silent

# Custom Colors
PURPLE				=	\033[1;35m
LIGHT_GREEN			=	\033[1;32m
RESET				=	\033[0m

# Custom messages
EXE_DONE			=	@echo "$(PURPLE)🎉 $(NAME) compiled! 🎉$(RESET)\n"
BONUS_DONE			=	@echo "$(PURPLE)🎉 $(BNAME) compiled! 🎉$(RESET)\n"
ALL_CLEAN			=	@echo "🧹$(LIGHT_GREEN) Project's objects cleaned! 🧹$(RESET)\n"
ALL_FCLEAN			=	@echo "🧹$(LIGHT_GREEN) Project's objects & Executables cleaned! 🧹$(RESET)\n"

# Rules

all : libft
	@if [ ! -f minilibx-linux/libmlx.a ]; then \
		make -j4 -C minilibx-linux; \
	fi
	@make -j4 $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIB) $(MLX_LIB) $(MLX_FLAGS) -o $(NAME)
	$(EXE_DONE)

$(OBJ_FOLDER)/%.o: srcs/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

clean :
	@make clean -C libft
	@rm -rf $(OBJ_FOLDER)
	$(ALL_CLEAN)

fclean :
	@make fclean -C libft
	@rm -f $(NAME)
	@rm -rf $(OBJ_FOLDER)
	$(ALL_FCLEAN)

re : fclean all

libft : 
	make -C ./libft -j4

.PHONY: all clean fclean re libft

-include $(DEPS)
