NAME	=	minitalk
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror

SERVER		=	server
SERVER_SRC	=	server.c
SERVER_OBJ	=	$(SERVER_SRC:%.c=%.o)

CLIENT		=	client
CLIENT_SRC	=	client.c
CLIENT_OBJ	=	$(CLIENT_SRC:%.c=%.o)


%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY:	all
all: $(NAME)


$(SERVER): $(SERVER_OBJ)
	$(CC) $(CFLAGS) $(SERVER_OBJ) -o $(SERVER)

$(CLIENT):	$(CLIENT_OBJ)
	$(CC) $(CFLAGS) $(CLIENT_OBJ) -o $(CLIENT)

$(NAME):	$(SERVER) $(CLIENT)

.PHONY:	clean
clean:
	rm -rf $(SERVER_OBJ) $(CLIENT_OBJ)

.PHONY: fclean
fclean: clean
	rm -rf $(SERVER) $(CLIENT)

.PHONY:	re
re: fclean all