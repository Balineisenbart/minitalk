GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

SRCDIR = .
SERVER_SRCS = server.c utils.c
CLIENT_SRCS = client.c  utils.c

SERVER_OBJS = $(SERVER_SRCS:%.c=%.o)
CLIENT_OBJS = $(CLIENT_SRCS:%.c=%.o)

#targets
SERVER = server
CLIENT = client

#LIBFT_DIR = include/libft
#FT_PRINTF_DIR = include/ft_printf

#LIBFT = $(LIBFT_DIR)/libft.a
#FT_PRINTF = $(FT_PRINTF_DIR)/ft_printf.a


all: $(SERVER) $(CLIENT)

#%.o:	%.c
#	$(CC) $(CFLAGS) -I$(LIBFT_DIR) -I$(FT_PRINTF_DIR) -c $< -o $@

$(SERVER):	$(SERVER_OBJS)
#	@make -C $(LIBFT_DIR)
#	@make -C $(FT_PRINTF_DIR)
	$(CC) $(CFLAGS) $^ -L$(LIBFT_DIR) -lft -L$(FT_PRINTF_DIR) -lft -o $(SERVER)
	@echo "$(GREEN)Built $(SERVER)$(RESET)"

$(CLIENT):	$(CLIENT_OBJS)
#	@make -C $(LIBFT_DIR)
#	@make -C $(FT_PRINTF_DIR)
	$(CC) $(CFLAGS) $^ -L$(LIBFT_DIR) -lft -L$(FT_PRINTF_DIR) -lft -o $(CLIENT)
	@echo "$(GREEN)Built $(SERVER)$(RESET)"

clean:
#	@make clean -C $(LIBFT_DIR)
#	@make clean -C $(FT_PRINTF_DIR)
	rm -f $(SERVER_OBJS) $(CLIENT_OBJS)
	@echo "$(RED)Cleaned object files$(RESET)"

fclean: clean
#	@make clean -C $(LIBFT_DIR)
#	@make clean -C $(FT_PRINTF_DIR)
	rm -f $(SERVER) $(CLIENT)
	@echo "$(RED)Cleaned binaries$(RESET)"

re:	fclean all
	@echo "$(GREEN)Rebuilding Library$(RESET)"

.PHONY: clean fclean re all $(LIBFT_DIR) $(FT_PRINTF_DIR)