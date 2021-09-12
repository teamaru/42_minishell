/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsugiyam <tsugiyam@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 17:04:48 by tsugiyam          #+#    #+#             */
/*   Updated: 2020/10/08 17:11:18 by tsugiyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	unsigned int	i;
	unsigned int	j;
	size_t			dest_size;
	size_t			src_size;

	i = 0;
	while (dst[i])
		i++;
	dest_size = i;
	src_size = 0;
	while (src[src_size])
		src_size++;
	if (dest_size >= dstsize)
		return (src_size + dstsize);
	j = 0;
	while (src[j] && j < dstsize - dest_size - 1)
		dst[i++] = src[j++];
	dst[i] = '\0';
	return (dest_size + src_size);
}
