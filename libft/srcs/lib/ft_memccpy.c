/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsugiyam <tsugiyam@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 16:56:38 by tsugiyam          #+#    #+#             */
/*   Updated: 2021/05/11 22:25:55 by tsugiyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned int	i;
	unsigned char	*res;
	unsigned char	*uc_src;
	unsigned char	uc_c;

	i = -1;
	res = (unsigned char *)dst;
	uc_src = (unsigned char *)src;
	uc_c = (unsigned char)c;
	while (++i < n && uc_src[i] != uc_c)
		res[i] = uc_src[i];
	if (uc_src[i] == uc_c)
	{
		res[i] = uc_src[i];
		return (res + i + 1);
	}
	if (i >= n)
		return (NULL);
	else
		return (res);
}
