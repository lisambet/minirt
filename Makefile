NAME = minirt

SRCS = main.c \
	ray.c \
	vec1.c \
	vec2.c \
	init.c \
	events.c \
	objects.c \
	cleanup.c \
	light.c \
	cylinder.c \
	hit_cylinder.c \
	get_normal.c \
	shadow.c \

OBJS = $(SRCS:.c=.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror -I ./minilibx-linux
LDFLAGS = -L ./minilibx-linux -lmlx -lXext -lX11 -lm

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
