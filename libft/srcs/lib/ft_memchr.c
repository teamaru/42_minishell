/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsugiyam <tsugiyam@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 16:57:01 by tsugiyam          #+#    #+#             */
/*   Updated: 2020/10/08 16:57:16 by tsugiyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned int	i;
	unsigned char	*str;

	i = -1;
	str = (unsigned char *)s;
	while (++i < n)
	{
		if (str[i] == (unsigned char)c)
			return (str + i);
	}
	return (NULL);
}
