MINISHL  := minishell
CC       := gcc
CFLAGS   := -Wall -Wextra -Werror
INCLUDE  := -I./includes
SRCDIR   := ./srcs/
SRCS     := $(wildcard $(SRCDIR)*.c) $(wildcard $(SRCDIR)*/*.c)
OBJS     := $(SRCS:.c=.o)
DEPS     := $(SRCS:%.c=%.d)
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
	$(CC) $(CFLAGS) $(INCLUDE) -c -MMD -MP -MF $(<:.c=.d) -o $@ $<

-include $(DEPS)

.PHONY: clean
clean:
	$(RM) $(OBJS) $(DEPS)
	$(MAKE) fclean -C $(LIBFTDIR)

fclean: clean
	$(RM) $(MINISHL)

debug: $(LIBFT)
	$(CC) -g -o $(MINISHL) $(INCLUDE) $(SRCS) $(LIBFT) $(RDLNFLG)

re: fclean all
