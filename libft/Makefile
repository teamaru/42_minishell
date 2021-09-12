# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tsugiyam <tsugiyam@student.42tokyo.>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/09 16:43:31 by tsugiyam          #+#    #+#              #
#    Updated: 2020/10/09 16:43:37 by tsugiyam         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC       := gcc
CFLAGS   := -Wall -Wextra -Werror
NAME     := libft
INCLUDE  := -I./includes
SRCDIR   := ./srcs/
LIBDIR   := $(SRCDIR)lib/
GNLDIR   := $(SRCDIR)get_next_line/
PRNTFDIR := $(SRCDIR)ft_printf/
SRCS     := $(LIBDIR)ft_memset.c $(LIBDIR)ft_memcmp.c $(LIBDIR)ft_memcpy.c $(LIBDIR)ft_memccpy.c $(LIBDIR)ft_memmove.c \
		        $(LIBDIR)ft_memchr.c $(LIBDIR)ft_bzero.c $(LIBDIR)ft_strlen.c $(LIBDIR)ft_strlcpy.c $(LIBDIR)ft_strlcat.c \
		        $(LIBDIR)ft_strncmp.c $(LIBDIR)ft_strchr.c $(LIBDIR)ft_strrchr.c $(LIBDIR)ft_strnstr.c $(LIBDIR)ft_isalpha.c \
		        $(LIBDIR)ft_isdigit.c $(LIBDIR)ft_isalnum.c $(LIBDIR)ft_isascii.c $(LIBDIR)ft_isprint.c $(LIBDIR)ft_atoi.c \
		        $(LIBDIR)ft_toupper.c $(LIBDIR)ft_tolower.c $(LIBDIR)ft_calloc.c $(LIBDIR)ft_strdup.c \
		        $(LIBDIR)ft_itoa.c $(LIBDIR)ft_putchar_fd.c $(LIBDIR)ft_putendl_fd.c $(LIBDIR)ft_putnbr_fd.c $(LIBDIR)ft_putstr_fd.c \
		        $(LIBDIR)ft_split.c $(LIBDIR)ft_strjoin.c $(LIBDIR)ft_strmapi.c $(LIBDIR)ft_strtrim.c $(LIBDIR)ft_substr.c \
			      $(LIBDIR)ft_lstnew.c $(LIBDIR)ft_lstadd_front.c $(LIBDIR)ft_lstsize.c $(LIBDIR)ft_lstlast.c $(LIBDIR)ft_lstadd_back.c \
            $(LIBDIR)ft_lstdelone.c $(LIBDIR)ft_lstclear.c $(LIBDIR)ft_lstiter.c $(LIBDIR)ft_lstmap.c \
			      $(LIBDIR)ft_strcmp.c $(LIBDIR)ft_strndup.c $(LIBDIR)ft_strchr_i.c $(LIBDIR)ft_nbrlen.c \
						$(GNLDIR)get_next_line.c $(GNLDIR)utils.c \
			      $(PRNTFDIR)ft_printf.c $(PRNTFDIR)input.c $(PRNTFDIR)output.c $(PRNTFDIR)padding.c $(PRNTFDIR)utils.c
OBJDIR   := $(SRCDIR)
OBJS     := $(SRCS:.c=.o)
ARFLAGS  := rc

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(ARFLAGS) $(NAME) $(OBJS)

.c.o:
	$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $<

.PHONY: clean
clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all
