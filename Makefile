GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
INCLUDEDIR = include
FT_PRINTF_PATH = include/ft_printf
LIBF_PATH = include/libft

SRCDIR = .
SRCS = client.c server.c utils.c ft_strlen.c ft_atoi.c

OBJS = $(SRCS:.c=.o)

FT_PRINTF = $(FT_PRINTF_PATH)/ft_printf.a
LIBFT = $(LIBF_PATH)/libft.a

TARGET = serve client

all: $(TARGET)

server:	server server.c
	@$(CC) $(CFLAGS) $(OBJS) -o  $(TARGET)
	@make ft_printf
	@make libft

client: client client.c
	@$(CC) $(CFLAGS) $(OBJS) -o  $(TARGET)
	@make ft_printf
	@make libft

$(TARGET):	$(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o  $(TARGET)
	@echo "$(TARGET): $(GREEN)object files were created$(RESET)"
	@echo "$(TARGET): $(GREEN)$(TARGET) was created$(RESET)"

$(FT_PRINTF):
	@$(MAKE) -C $(FT_PRINTF_PATH)

%.o:	%.c
	$(CC) $(CFLAGS) -I$(INCLUDEDIR) -Ilibs -I$(FT_PRINTF_PATH) -I$(LIBFT_PATH) -c $< -o $@

clean:
	rm -f $(OBJS)
	@echo "$(RED)Cleaned object files$(RESET)"

fclean: clean
	rm -f $(NAME)
	@echo "$(RED)Cleaned targets$(RESET)"

re:	fclean all
	@echo "$(GREEN)Rebuilding Library$(RESET)"

.PHONY: clean fclean re all