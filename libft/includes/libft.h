/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsugiyam <tsugiyam@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 18:57:53 by tsugiyam          #+#    #+#             */
/*   Updated: 2021/05/11 18:49:41 by tsugiyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdio.h>
# include <stdlib.h>
# include <stdarg.h>
# include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# define MAX_FD 1024
# define DEC "0123456789"
# define L_HEX "0123456789abcdef"
# define U_HEX "0123456789ABCDEF"
# define FLAGS "-0"
# define SPECS "cspdiuxX%"

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

typedef enum e_flgs
{
	MINUS,
	ZERO,
}				t_flg;

typedef enum e_cmp
{
	MAX,
	MIN,
}				t_cmp;

typedef enum e_toggle
{
	PRE,
	SUF,
	FLD,
	ACC,
}				t_toggle;

typedef struct s_format
{
	t_flg	flgs[2];
	int		field;
	int		accuracy;
	int		specifier;
	int		output_size;
}				t_format;

/*
***********
** utils **
***********
*/
void			*ft_memset(void *b, int c, size_t len);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			*ft_memccpy(void *dst, const void *src, int c, size_t n);
void			*ft_memmove(void *dst, const void *src, size_t len);
void			*ft_memchr(const void *s, int c, size_t n);
void			ft_bzero(void *s, size_t n);
char			*ft_strchr(const char *s, int c);
char			*ft_strrchr(const char *s, int c);
char			*ft_strnstr(const char *haystack,
					const char *needle, size_t len);
size_t			ft_strlen(const char *s);
size_t			ft_strlcpy(char *dst, const char *restrict src, size_t dstsize);
size_t			ft_strlcat(char *dst, const char *src, size_t dstsize);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_isalnum(int c);
int				ft_isascii(int c);
int				ft_isprint(int c);
int				ft_atoi(const char *str);
int				ft_tolower(int c);
int				ft_toupper(int c);
char			*ft_strdup(const char *s1);
void			*ft_calloc(size_t count, size_t size);

char			*ft_itoa(int n);
void			ft_putchar_fd(char c, int fd);
void			ft_putendl_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);
void			ft_putstr_fd(char *s, int fd);
char			**ft_split(char const *s, char c);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char			*ft_strtrim(char const *s1, char const *set);
char			*ft_substr(char const *s, unsigned int start, size_t len);

t_list			*ft_lstnew(void *content);
void			ft_lstadd_front(t_list **lst, t_list *new);
int				ft_lstsize(t_list *lst);
t_list			*ft_lstlast(t_list *lst);
void			ft_lstadd_back(t_list **lst, t_list *new);
void			ft_lstdelone(t_list *lst, void (*del)(void *));
void			ft_lstclear(t_list **lst, void (*del)(void *));
void			ft_lstiter(t_list *lst, void (*f)(void *));
t_list			*ft_lstmap(t_list *lst,
					void *(*f)(void *), void (*del)(void *));

char			*ft_strndup(char *src, int size);
int				ft_strchr_i(const char *s, int c);
int				ft_nbrlen(int nbr);

/*
*******************
** get_next_line **
*******************
*/
int				get_next_line(int fd, char **line);
int				add_memory(char **memory, char *left, char *right);
void			renew_memory(char **memory, char *new);
/*
***************
** ft_printf **
***************
*/
void			init_format(t_format *input);
int				ft_put_format(va_list args, t_format *input);
int				ft_check_format(const char **format,
					t_format *input, va_list args);
int				ft_print_format(const char *format,
					va_list args, t_format *input);
int				ft_printf(const char *format, ...);

void			ft_check_flg(const char **format, t_format *input);
int				ft_check_aster(const char **format, t_format *input,
					va_list args, t_toggle toggle);
int				ft_check_field_accuracy(const char **format, t_format *input,
					va_list args, t_toggle toggle);
void			ft_check_period(const char **format, t_format *input);
void			ft_check_specifier(const char **format, t_format *input);

int				ft_put_non_format(const char **format);
void			ft_putchar(t_format *input, char c);
void			ft_put_addr(t_format *input, void *addr);
void			ft_putstr(t_format *input, char *s);
void			ft_putnbr(t_format *input, char *nbr);

int				ft_put_accuracy(t_format *input, int nbr_size, int is_neg);
int				ft_padding(t_format *input);
int				ft_put_padding(t_format *input, t_toggle toggle);
int				ft_put_minus(void);
void			remove_minus(char **nbr);

void			ft_putstr_n(const char *s, int n);
int				ft_cmp(int nbr1, int nbr2, t_cmp cmp);
int				ft_strchr_i(const char *s, int c);
int				get_nbr_size(unsigned long nbr, char *base);
char			*convert_base(unsigned long src, char *base);

#endif
