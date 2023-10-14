# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mwallage <mwallage@student.42berlin.d      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/14 16:38:57 by mwallage          #+#    #+#              #
#    Updated: 2023/10/14 17:23:10 by mwallage         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror -pthread
SRCDIR		:= ./src
OBJDIR		:= ./obj
INCDIR		:= ./inc
LIBFTDIR	:= ./lib
LIBFT		:= $(LIBFTDIR)/libft.a
HEADERS		:= -I $(INCDIR) -I $(LIBFTDIR)/inc
LIBS		:= -L $(LIBFTDIR) -lft
SRC			:= main.c
SRCS		:= $(addprefix $(SRCDIR)/, $(SRC))
OBJS		:= $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))
NAME		:= philo

all: $(NAME)

$(LIBFTDIR):
	git clone https://github.com/MartijnWallage/42_libft.git $@

$(LIBFT): $(LIBFTDIR)
	make -C$(LIBFTDIR)

$(OBJDIR):
	mkdir obj

$(NAME): $(LIBFT) $(OBJDIR) $(OBJS)
	$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(INCDIR)/philo.h
	$(CC) -c $(CFLAGS) $< -o $@ $(HEADERS)

clean:
	rm -rf $(OBJS)
	make clean -C$(LIBFTDIR)

fclean: clean
	rm $(NAME)
	rmdir $(OBJDIR)
	rm -rf $(LIBFTDIR)

re: fclean all

.PHONY: all, clean, fclean, re
