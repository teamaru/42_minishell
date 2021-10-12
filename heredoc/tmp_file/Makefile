HEREDOC  := heredoc
CC       := gcc
CFLAGS   := -Wall -Wextra -Werror
INCLUDE  := -I./includes -I/usr/local/opt/readline/include
SRCDIR   := ./srcs/
SRCS     := $(wildcard $(SRCDIR)*.c) $(wildcard $(SRCDIR)*/*.c)
OBJS     := $(SRCS:.c=.o)
DEPS     := $(SRCS:%.c=%.d)
LIBFTDIR := ../../libft/
LIBFT    := $(LIBFTDIR)libft
MAKEFLGS := -C
RDLNFLG  := -lreadline -L/usr/local/opt/readline/lib
RM       := rm -rf

all: $(HEREDOC)

$(HEREDOC): $(OBJS) $(LIBFT)
	$(CC) -o $(HEREDOC) $(INCLUDE) $(OBJS) $(LIBFT) $(RDLNFLG)

$(LIBFT):
	$(MAKE) $(MAKEFLGS) $(LIBFTDIR)

.c.o:
	$(CC) $(CFLAGS) $(INCLUDE) -c -MMD -MP -MF $(<:.c=.d) -o $@ $<

-include $(DEPS)

.PHONY: clean
clean:
	$(RM) $(OBJS) $(DEPS) $(HEREDOC).dSYM
	$(MAKE) fclean -C $(LIBFTDIR)

fclean: clean
	$(RM) $(HEREDOC)

debug: $(LIBFT)
	$(CC) -g -o $(HEREDOC) $(INCLUDE) $(SRCS) $(LIBFT) $(RDLNFLG)

re: fclean all debug
