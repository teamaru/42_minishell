REDIRECT := redirect
CC := gcc
CFLAGS := -Wall -Wextra -Werror
INCLUDE := -I./
SRCS := main.c \
		append.c \
		create_t_redirection_list.c \
		input.c \
		output.c

OBJS := $(SRCS:.c=.o)
DEPS := $(SRCS:%.c=%.d)
LIBFTDIR := ../../libft/
LIBFT := $(LIBFTDIR)libft
MAKEFLGS := -C

RM := rm -f

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
	$(RM) $(OBJS) $(DEPS)

fclean:
	$(MAKE) $(MAKEFLGS) $(LIBFTDIR) fclean
	$(RM) $(OBJS) $(DEPS) $(REDIRECT)

test: $(LIBFT)
	$(CC) -g $(CFLAGS) $(SRCS) $(LIBFT) $(INCLUDE) -o $(REDIRECT)

re: fclean all
