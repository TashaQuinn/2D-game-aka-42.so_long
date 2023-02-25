CFLAGS 		:= -Wall -Wextra -Werror
NAME 		:= starry_night_2d
LIBFT		:= ./libs/libft/srcs/
LIBMLX 		:= ./libs/MLX/
HEADERS 	:= -I includes -I libs/libft/srcs -I libs/MLX/include
OS 			:= $(shell uname -s)
ARCH 		:= $(shell uname -m)
DEBUG 		:= -fsanitize=address
SCRS 		:= libs/libft/srcs/*.c srcs/*.c

# determining architecture
ifeq ($(ARCH), arm)
GLFW 		:= libs/MLX/lib/lib-arm64/libglfw3.a
else 
GLFW 		:= libs/MLX/lib/lib-universal/libglfw3.a
endif

# cross-platform compatibility
ifeq ($(OS), Darwin)
LIBS		:= -framework Cocoa -framework OpenGL, -framework IOKit $(GLFW)
else ifeq ($(OS), Linux)
LIBS		:= -ldl -lglfw
endif

all : $(OBJS) libft libmlx compile

%.o : %.c
	@$(CC) $(CFLAGS) -c $< -o $@

libft:
	@$(MAKE) -C $(LIBFT)

libmlx:
	@$(MAKE) -C $(LIBMLX)

compile: libft libmlx
	$(CC) $(CFLAGS) -g $(HEADERS) $(LIBS) $(SCRS) $(LIBMLX)libmlx42.a $(LIBFT)libft.a $(DEBUG) -o $(NAME) 

convert:
	@python3 libs/MLX/tools/xpm3_conv.py textures/$(IMG).xpm

clean:
	@rm -rf $(OBJS)
	@$(MAKE) -C $(LIBFT) clean
	@$(MAKE) -C $(LIBMLX) clean

fclean: clean
	@rm -rf $(NAME)
	@$(MAKE) -C $(LIBFT) fclean
	@$(MAKE) -C $(LIBMLX) fclean

re: fclean all

.PHONY: all, libft, libmlx, compile, convert, clean, fclean, re
