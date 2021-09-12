MINISHL  := minishell
CC       := gcc
CFLAGS   := -Wall -Wextra -Werror
INCLUDE  := -I./includes
SRCDIR   := ./srcs/
SRCS     := $(wildcard $(SRCDIR)*.c) $(wildcard $(SRCDIR)*/*.c)
OBJS     := $(SRCS:.c=.o)
LIBFTDIR := ./libft/
LIBFT    := $(LIBFTDIR)libft
MAKEFLGS := -C
RDLNFLG  := -lreadline

all: $(MINISHL)

$(MINISHL): $(OBJS) $(LIBFT)
	$(CC) -o $(MINISHL) $(INCLUDE) $(OBJS) $(LIBFT) $(RDLNFLG)

$(LIBFT):
	$(MAKE) $(MAKEFLGS) $(LIBFTDIR)

.c.o:
	$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $<

.PHONY: clean
clean:
	$(RM) $(OBJS)
	$(MAKE) fclean -C $(LIBFTDIR)

fclean: clean
	$(RM) $(MINISHL)

re: fclean all
