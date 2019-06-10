# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/03/29 17:02:39 by tiboitel          #+#    #+#              #
#    Updated: 2019/04/04 17:07:33 by tiboitel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = clang
CFLAGS = -Wall -Werror -Wextra -g
LIBFT_DIRECTORY=./libft/
LIBFT_INCLUDES_DIRECTORY=./libft/includes
INCLUDES_DIRECTORY=./includes/ftp

# SHARED SECTION
SRC_PATH_SHARED=srcs/shared/
SRCS_SHARED=$(SRC_PATH_SHARED)error.c \
			$(SRC_PATH_SHARED)endpoint.c \
			$(SRC_PATH_SHARED)command.c

# SERVER SECTION
NAME_SERVER		=serveur
SRCS_PATH_SERVER=srcs/server/
SRCS_SERVER		=$(SRCS_PATH_SERVER)main.c \
				 $(SRCS_PATH_SERVER)server.c \
				 $(SRCS_PATH_SERVER)receiver.c \
				 $(SRCS_PATH_SERVER)handlers.c \
				 $(SRCS_PATH_SERVER)error.c \
				 $(SRCS_PATH_SERVER)dispatcher.c \
				 $(SRCS_PATH_SERVER)response.c \
				 $(SRCS_PATH_SERVER)execute.c \
				 $(SRCS_PATH_SERVER)cd.c \
				$(SRCS_SHARED)
O_SERVER=$(SRCS_SERVER:.c=.o)

# CLIENT SECTION
NAME_CLIENT		=client
SRCS_PATH_CLIENT=srcs/client/
SRCS_CLIENT		=$(SRCS_PATH_CLIENT)main.c \
				 $(SRCS_PATH_CLIENT)client.c \
				$(SRCS_SHARED)
O_CLIENT		=$(SRCS_CLIENT:.c=.o)

all: $(NAME_CLIENT) $(NAME_SERVER)

$(NAME_CLIENT): $(O_CLIENT)
	make -C libft
	$(CC) -o $(NAME_CLIENT) $(CFLAGS) $(O_CLIENT) -I $(INCLUDES_DIRECTORY) -I $(LIBFT_INCLUDES_DIRECTORY) -L $(LIBFT_DIRECTORY) -lft -Wuninitialized

$(NAME_SERVER): $(O_SERVER)
	make -C libft
	$(CC) -o $(NAME_SERVER) $(CFLAGS) $(O_SERVER) -I $(INCLUDES_DIRECTORY) -I $(LIBFT_INCLUDES_DIRECTORY) -L $(LIBFT_DIRECTORY) -lft -Wunitialized

%.o: %.c
	$(CC) -o $@ -I $(INCLUDES_DIRECTORY) -I $(LIBFT_INCLUDES_DIRECTORY) $(CFLAGS) -c $<

libft:
	make -C $(LIBFT_DIRECTORY)

clean: 
	make -C $(LIBFT_DIRECTORY) clean
	rm -rf $(NAME_SERVER).dSYM
	rm -rf $(NAME_CLIENT).dSYM
	rm -rf $(O_SERVER)
	rm -rf $(O_CLIENT)
	rm -rf $(O_SHARED)

fclean: clean
	make -C $(LIBFT_DIRECTORY) fclean
	rm -rf $(NAME_SERVER)
	rm -rf $(NAME_CLIENT)

re: fclean all

.PHONY: all libft clean fclean re
