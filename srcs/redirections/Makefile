REDIRECT := redirect
CC := gcc
CFLAGS := -Wall -Wextra -Werror
INCLUDE := -I./
SRCS := main.c \
		change_reference.c \
		create_t_redirection_list.c \
		execution.c \
		free.c

OBJS := $(SRCS:.c=.o)
DEPS := $(SRCS:%.c=%.d)
LIBFTDIR := ../../libft/
LIBFT := $(LIBFTDIR)libft
MAKEFLGS := -C

RM := rm -rf

all: $(REDIRECT)

$(REDIRECT): $(OBJS) $(LIBFT)
	$(CC) -o $(REDIRECT) $(INCLUDE) $(OBJS) $(LIBFT)

$(LIBFT):
	$(MAKE) $(MAKEFLGS) $(LIBFTDIR)

.c.o:
	$(CC) -g $(CFLAGS) $(INCLUDE) -c -MMD -MP -MF $(<:.c=.d) $< -o $@

-include $(DEPS)

clean:
	$(MAKE) $(MAKEFLGS) $(LIBFTDIR) clean
	$(RM) $(OBJS) $(DEPS) $(REDIRECT).dSYM

fclean:
	$(MAKE) $(MAKEFLGS) $(LIBFTDIR) fclean
	$(RM) $(OBJS) $(DEPS) $(REDIRECT).dSYM $(REDIRECT)

test: $(LIBFT)
	$(CC) -g $(CFLAGS) $(SRCS) $(LIBFT) $(INCLUDE) -o $(REDIRECT)

re: fclean all
