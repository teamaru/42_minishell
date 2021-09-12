/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsugiyam <tsugiyam@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 16:04:59 by tsugiyam          #+#    #+#             */
/*   Updated: 2021/05/11 22:35:55 by tsugiyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"
#include <stdlib.h>

char	*ft_strndup(char *src, int size)
{
	int		i;
	char	*res;

	res = malloc(size + 1);
	if (!res)
		return (NULL);
	i = -1;
	while (++i < size)
		res[i] = src[i];
	res[i] = '\0';
	return (res);
}
