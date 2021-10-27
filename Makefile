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
READLINECONFIG := $(shell find ~/.inputrc -type f -print | xargs grep 'set echo-control-characters off' )
ifeq ($(READLINECONFIG),set echo-control-characters off)
else
	@echo "set echo-control-characters off" >> ~/.inputrc
	@echo "${HOME}/.inputrc setting now!!"
endif

MINISHL_LEAKS	:= minishell_leaks
SRCS_LEAKS	:= ./test/help/leaks.c
INCLUDE_LEAKS := -I./test/help

ifdef LEAKS
MINISHL := $(MINISHL_LEAKS)
endif

all: $(MINISHL)

$(MINISHL): $(OBJS) $(LIBFT)
	$(CC) -o $(MINISHL) $(INCLUDE) $(OBJS) $(LIBFT) $(RDLNFLG) $(LDFLAGS)

$(LIBFT):
	$(MAKE) $(MAKEFLGS) $(LIBFTDIR)

.c.o:
	$(CC) $(CFLAGS) $(INCLUDE) -c -MMD -MP -MF $(<:.c=.d) -o $@ $<

-include $(DEPS)

clean:
	$(RM) $(OBJS) $(DEPS)
	$(MAKE) fclean -C $(LIBFTDIR)

fclean: clean
	$(RM) $(MINISHL)

re: fclean all

debug: $(LIBFT)
	$(CC) -g -o $(MINISHL) $(INCLUDE) -I $(shell brew --prefix readline)/include $(SRCS) $(LIBFT) $(RDLNFLG) $(LDFLAGS)

leaks: $(LIBFT)
	$(MAKE) CFLAGS="$(CFLAGS) -D LEAKS=1" INCLUDE="$(INCLUDE) $(INCLUDE_LEAKS)" SRCS="$(SRCS) $(SRCS_LEAKS)" LEAKS=TRUE

cleanleaks: clean
	$(RM) ./test/help/leaks.o ./test/help/leaks.d

fcleanleaks: cleanleaks
	$(RM) $(MINISHL_LEAKS)

.PHONY: all clean fclean debug re leaks cleanleaks fcleanleaks
