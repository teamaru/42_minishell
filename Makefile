MINISHL  := minishell
CC       := gcc
CFLAGS   := -Wall -Wextra -Werror -I $(shell brew --prefix readline)/include
INCLUDE  := -I./includes
SRCDIR   := ./srcs/
SRCS     := $(wildcard $(SRCDIR)*.c) $(wildcard $(SRCDIR)*/*.c)
OBJS     := $(SRCS:.c=.o)
LIBFTDIR := ./libft/
LIBFT    := $(LIBFTDIR)libft
MAKEFLGS := -C
RDLNFLG  := -lreadline
LDFLAGS  := -lreadline -lhistory -L$(shell brew --prefix readline)/lib

all: $(MINISHL)

$(MINISHL): $(OBJS) $(LIBFT)
	$(CC) -o $(MINISHL) $(INCLUDE) $(OBJS) $(LIBFT) $(RDLNFLG) $(LDFLAGS)

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
