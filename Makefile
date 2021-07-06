NAME	=	minitalk
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror
LDFLAGS	=	-L$(LIBFTDIR) $(patsubst lib%,-l%,$(basename $(LIBFT)))

LIBFT		=	libft.a
LIBFTDIR	=	libft

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
	$(CC) $(CFLAGS) $(SERVER_OBJ) $(LDFLAGS) -o $(SERVER)

$(CLIENT):	$(CLIENT_OBJ)
	$(CC) $(CFLAGS) $(CLIENT_OBJ) $(LDFLAGS) -o $(CLIENT)

$(NAME):	$(SERVER) $(CLIENT)

.PHONY:	clean
clean:
	rm -rf $(SERVER_OBJ) $(CLIENT_OBJ)

.PHONY: fclean
fclean: clean
	rm -rf $(SERVER) $(CLIENT)

.PHONY:	re
re: fclean all
