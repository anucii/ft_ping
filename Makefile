# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jdaufin <jdaufin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/15 18:18:37 by jdaufin           #+#    #+#              #
#    Updated: 2020/11/20 12:18:33 by jdaufin          ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

.PHONY: test re clean bclean fclean

CC = clang
# TODO : remove debug flag (-g)
CFLAGS = -Wall -Wextra -Werror -g

NAME = ft_ping

SRCDIR = srcs/
OBJDIR = builds/
HDRDIR = includes/
LIBDIR = libft/
LIBHDRDIR = $(addsuffix includes/, $(LIBDIR))

FILES = ft_ping parse_args set_options show_help show_errors parse_address \
		resolve_address dynarray_init dynarray_add dynarray_free \
		dynarray_getbuflen handle_cycle send_echo handle_reply \
		handle_reply_utils
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

bclean : 
		rm -rf $(OBJDIR)

clean : bclean
		make -C $(LIBDIR) clean

fclean : bclean
		make -C $(LIBDIR) fclean
		rm -rf $(NAME)

re : fclean $(NAME)

test : $(NAME)
		./$(NAME) -c 4 8.8.8.8