/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsugiyam <tsugiyam@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 17:01:06 by tsugiyam          #+#    #+#             */
/*   Updated: 2021/05/11 22:30:27 by tsugiyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "./libft.h"

static void	*free_memory(char **res, int i)
{
	while (--i >= 0)
		free(res[i]);
	free(res);
	return (NULL);
}

static char	**split_str(const char *s, char c, unsigned int size)
{
	int		i;
	int		len;
	char	**res;

	res = malloc(sizeof(char *) * (size + 1));
	if (!res)
		return (NULL);
	i = 0;
	res[size] = NULL;
	while (size--)
	{
		len = 0;
		while (*s && *s == c)
			s++;
		while (s[len] && s[len] != c)
			len++;
		res[i] = malloc(len + 1);
		if (!res[i])
			return (free_memory(res, i));
		ft_strlcpy(res[i++], s, len + 1);
		s += len;
	}
	return (res);
}

static int	take_size(char const *s, char c)
{
	unsigned int	size;

	size = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (!*s)
			break ;
		while (*s && *s != c)
			s++;
		size++;
	}
	return (size);
}

char	**ft_split(char const *s, char c)
{
	unsigned int	size;

	if (!s)
		return (NULL);
	size = take_size(s, c);
	return (split_str(s, c, size));
}
