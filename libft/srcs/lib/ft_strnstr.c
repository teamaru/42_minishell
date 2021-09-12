/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsugiyam <tsugiyam@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 17:07:25 by tsugiyam          #+#    #+#             */
/*   Updated: 2021/05/11 22:37:40 by tsugiyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	temp;

	if (!(*needle))
		return ((char *)(haystack));
	i = -1;
	while (haystack[++i] && i < len)
	{
		if (haystack[i] == needle[0])
		{
			temp = i;
			j = 1;
			while (needle[j] && haystack[++temp] == needle[j])
				j++;
			if (temp >= len)
				break ;
			if (!needle[j])
				return ((char *)(haystack + i));
		}
	}
	return (NULL);
}
