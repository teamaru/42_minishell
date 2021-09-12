/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsugiyam <tsugiyam@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 17:08:17 by tsugiyam          #+#    #+#             */
/*   Updated: 2021/05/11 22:39:32 by tsugiyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "./libft.h"

static int	is_in_set(char c, char const *set)
{
	while (set && *set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	unsigned int	i;
	unsigned int	len;
	unsigned int	prefix;
	unsigned int	suffix;
	char			*res;

	if (!s1)
		return (NULL);
	len = ft_strlen(s1);
	prefix = 0;
	while (prefix < len && is_in_set(s1[prefix], set))
		prefix++;
	if (len == prefix)
		return (ft_strdup(""));
	suffix = 0;
	while (suffix < len && is_in_set(s1[len - 1 - suffix], set))
		suffix++;
	res = malloc(len - prefix - suffix + 1);
	if (!res)
		return (NULL);
	i = 0;
	while (prefix != len - suffix)
		res[i++] = s1[prefix++];
	res[i] = '\0';
	return (res);
}
