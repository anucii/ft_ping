# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jdaufin <jdaufin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/15 18:18:37 by jdaufin           #+#    #+#              #
#    Updated: 2020/10/16 17:11:09 by jdaufin          ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

.PHONY: test re clean fclean

CC = clang
CFLAGS = -Wall -Wextra -Werror

NAME = ft_ping

SRCDIR = srcs/
OBJDIR = builds/
HDRDIR = includes/
LIBDIR = libft/
LIBHDRDIR = $(addsuffix includes/, $(LIBDIR))

FILES = ft_ping
SRC = $(addprefix $(SRCDIR), $(addsuffix .c, $(FILES)))
OBJ = $(addprefix $(OBJDIR), $(addsuffix .o, $(FILES)))
HDR = $(addprefix $(HDRDIR), ft_ping.h)
LIBHDR = $(addprefix $(LIBHDRDIR), libft.h)
LIB = $(addprefix $(LIBDIR), libft.a)

$(NAME) :$(OBJ) $(LIB)
		$(CC) $(CFLAGS) -o $@ $^ -I $(HDRDIR) -L $(LIBDIR) -lft

$(LIB) :
		make -C $(LIBDIR)

$(OBJDIR)%.o : $(SRCDIR)%.c $(HDR) $(LIBHDR)
		[ -d $(OBJDIR) ] || mkdir $(OBJDIR)
		$(CC) $(CFLAGS) -o $@ -c $< -I $(HDRDIR) -I $(LIBHDRDIR)

clean : 
		rm -rf $(OBJDIR)

fclean : clean
		rm -rf $(NAME)

re : fclean $(NAME)

test : $(NAME)
		./$(NAME)