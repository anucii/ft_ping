# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jdaufin <jdaufin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/15 18:18:37 by jdaufin           #+#    #+#              #
#    Updated: 2020/10/15 23:10:32 by jdaufin          ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

.PHONY: test re clean fclean

CC = clang
CFLAGS = -Wall -Wextra -Werror -g

NAME = ft_ping

SRCDIR = srcs/
OBJDIR = builds/
HDRDIR = includes/

FILES = ft_ping get_local_address
SRC = $(addprefix $(SRCDIR), $(addsuffix .c, $(FILES)))
OBJ = $(addprefix $(OBJDIR), $(addsuffix .o, $(FILES)))
HDR = $(addprefix $(HDRDIR), ft_ping.h)

$(NAME) :$(OBJ)
		$(CC) $(CFLAGS) -o $@ $^ -I $(HDRDIR)

$(OBJDIR)%.o : $(SRCDIR)%.c $(HDR)
		[ -d $(OBJDIR) ] || mkdir $(OBJDIR)
		$(CC) $(CFLAGS) -o $@ -c $< -I $(HDRDIR)

clean : 
		rm -rf $(OBJDIR)

fclean : clean
		rm -rf $(NAME)

re : fclean $(NAME)

test : $(NAME)
		./$(NAME)