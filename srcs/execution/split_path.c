/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnakahod <jnakahod@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 23:15:58 by jnakahod          #+#    #+#             */
/*   Updated: 2021/10/25 23:30:46 by jnakahod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

static unsigned int	take_size(char *s, char delimiter)
{
	unsigned int	size;
	int				i;

	size = 0;
	i = -1;
	while (s[++i])
	{
		if (s[i] == delimiter)
			size++;
	}
	if (size)
		size++;
	return (size);
}

static void	*free_memory(char **res, int i)
{
	while (--i >= 0)
		free(res[i]);
	free(res);
	return (NULL);
}

static void	copy_path(char **path, char **str, int word_len)
{
	if (word_len)
	{
		ft_strlcpy(*path, *str, word_len + 1);
		*str += word_len;
	}
	else
		ft_strlcpy(*path, ".", 2);
	if ((*str)[0])
		*str += 1;
}

static char	**create_paths(char *str, char delimiter, unsigned int counts)
{
	char	**paths;
	int		word_len;
	int		i;

	paths = (char **)ft_calloc(counts + 1, sizeof(char *));
	if (!paths)
		return (NULL);
	i = 0;
	paths[counts] = NULL;
	while (counts--)
	{
		word_len = 0;
		while (str[word_len] && str[word_len] != delimiter)
			word_len += 1;
		if (word_len)
			paths[i] = (char *)ft_calloc(word_len + 1, sizeof(char));
		else
			paths[i] = (char *)ft_calloc(2, sizeof(char));
		if (!paths[i])
			return (free_memory(paths, i));
		copy_path(&paths[i], &str, word_len);
		i += 1;
	}
	return (paths);
}

char	**split_path(char *path, char delimiter)
{
	char			**paths;
	unsigned int	counts;

	counts = take_size(path, delimiter);
	paths = create_paths(path, delimiter, counts);
	return (paths);
}
