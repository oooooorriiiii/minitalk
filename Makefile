NAME	=	minitalk
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror

SERVER		=	server
SERVER_SRC	=	server.c
SERVER_OBJ	=	$(SERVER_SRC:%.c=%.o)

CLIENT		=	client
CLIENT_SRC	=	client.c
CLIENT_OBJ	=	$(CLIENT_SRC:%.c=%.o)

SRCS		=	utils.c
OBJS		=	$(SRCS:%.c=%.o)

SERVER_BONUS		=	server_bonus
SERVER_BONUS_SRC	=	server_bonus.c
SERVER_BONUS_OBJ	=	$(SERVER_BONUS_SRC:%.c=%.o)

CLIENT_BONUS		=	client_bonus
CLIENT_BONUS_SRC	=	client_bonus.c
CLIENT_BONUS_OBJ	=	$(CLIENT_BONUS_SRC:%.c=%.o)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY:	all
all: $(NAME)

$(SERVER): $(SERVER_OBJ) $(OBJS)
	$(CC) $(CFLAGS) $(SERVER_OBJ) $(OBJS) -o $(SERVER)

$(CLIENT):	$(CLIENT_OBJ) $(OBJS)
	$(CC) $(CFLAGS) $(CLIENT_OBJ) $(OBJS) -o $(CLIENT)

$(NAME):	$(SERVER) $(CLIENT)

.PHONY:	bonus
bonus: $(SERVER_BONUS) $(CLIENT_BONUS)

$(SERVER_BONUS): $(SERVER_BONUS_OBJ) $(OBJS)
	$(CC) $(CFLAGS) $(SERVER_BONUS_OBJ) $(OBJS) -o $(SERVER_BONUS)

$(CLIENT_BONUS): $(CLIENT_BONUS_OBJ) $(OBJS)
	$(CC) $(CFLAGS) $(CLIENT_BONUS_OBJ) $(OBJS) -o $(CLIENT_BONUS)

.PHONY:	clean
clean:
	rm -rf $(SERVER_OBJ) $(CLIENT_OBJ) $(OBJS)

.PHONY: fclean
fclean: clean
	rm -rf $(SERVER) $(CLIENT) $(SERVER_BONUS) $(CLIENT_BONUS)

.PHONY:	re
re: fclean all
