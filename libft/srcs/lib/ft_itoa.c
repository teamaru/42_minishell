/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsugiyam <tsugiyam@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 16:53:19 by tsugiyam          #+#    #+#             */
/*   Updated: 2021/05/11 22:22:13 by tsugiyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "./libft.h"

static	int	take_len(int n)
{
	int	len;

	if (n < 0)
		len = 2;
	else
		len = 1;
	n /= 10;
	while (n)
	{
		len++;
		n /= 10;
	}
	return (len);
}

int	check_minus(int n)
{
	if (n < 0)
		return (1);
	else
		return (0);
}

char	*ft_itoa(int n)
{
	unsigned int	len;
	unsigned int	num;
	int				is_neg;
	char			*res;

	len = take_len(n);
	res = malloc(len + 1);
	if (!res)
		return (NULL);
	is_neg = check_minus(n);
	if (is_neg)
		num = -n;
	else
		num = n;
	res[len] = '\0';
	while (len--)
	{
		res[len] = num % 10 + '0';
		num /= 10;
	}
	if (is_neg)
		res[0] = '-';
	return (res);
}
