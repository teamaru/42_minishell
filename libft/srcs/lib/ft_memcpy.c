/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsugiyam <tsugiyam@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 16:57:49 by tsugiyam          #+#    #+#             */
/*   Updated: 2020/10/08 16:58:04 by tsugiyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned int	i;
	unsigned char	*res;

	i = -1;
	if (!dst && !src)
		return (NULL);
	res = (unsigned char *)dst;
	while (++i < n)
		res[i] = ((unsigned char *)src)[i];
	return (res);
}
