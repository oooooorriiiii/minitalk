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

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY:	all
all: $(NAME)

$(SERVER): $(SERVER_OBJ) $(OBJS)
	$(CC) $(CFLAGS) $(SERVER_OBJ) $(OBJS) -o $(SERVER)

$(CLIENT):	$(CLIENT_OBJ) $(OBJS)
	$(CC) $(CFLAGS) $(CLIENT_OBJ) $(OBJS) -o $(CLIENT)

$(NAME):	$(SERVER) $(CLIENT)

.PHONY:	clean
clean:
	rm -rf $(SERVER_OBJ) $(CLIENT_OBJ)

.PHONY: fclean
fclean: clean
	rm -rf $(SERVER) $(CLIENT)

.PHONY:	re
re: fclean all
