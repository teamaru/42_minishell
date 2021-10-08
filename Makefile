MINISHL  := minishell
CC       := gcc
CFLAGS   := -Wall -Wextra -Werror -I $(shell brew --prefix readline)/include
INCLUDE  := -I./includes
SRCDIR   := ./srcs/
SRCS     := $(wildcard $(SRCDIR)*.c) $(wildcard $(SRCDIR)*/*.c)
OBJS     := $(SRCS:.c=.o)
DEPS     := $(SRCS:%.c=%.d)
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
	$(CC) $(CFLAGS) $(INCLUDE) -c -MMD -MP -MF $(<:.c=.d) -o $@ $<

-include $(DEPS)

.PHONY: clean
clean:
	$(RM) $(OBJS) $(DEPS)
	$(MAKE) fclean -C $(LIBFTDIR)

fclean: clean
	$(RM) $(MINISHL)

debug: $(LIBFT)
	$(CC) -g -o $(MINISHL) $(INCLUDE) -I $(shell brew --prefix readline)/include $(SRCS) $(LIBFT) $(RDLNFLG) $(LDFLAGS)

re: fclean all
