/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsugiyam <tsugiyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 19:56:03 by tsugiyam          #+#    #+#             */
/*   Updated: 2021/05/11 22:16:43 by tsugiyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "./libft.h"

long	overflow(int sign)
{
	if (sign == -1)
		return (LONG_MIN);
	else
		return (LONG_MAX);
}

int	to_int(const char *str, int sign)
{
	unsigned long	res;
	unsigned long	ov_div;
	int				ov_mod;
	int				is_overflow;

	ov_div = LONG_MAX / 10;
	ov_mod = LONG_MAX % 10;
	res = 0;
	is_overflow = 0;
	while (*str && '0' <= *str && *str <= '9')
	{
		if (res > ov_div || (res == ov_div && (*str - '0') > ov_mod))
			is_overflow = 1;
		else
		{
			res *= 10;
			res += (*str - '0');
		}
		str++;
	}
	if (is_overflow)
		res = overflow(sign);
	return (res * sign);
}

int	ft_atoi(const char *str)
{
	int	sign;

	while (*str == ' ' || ('\t' <= *str && *str <= '\r'))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str++ == '-')
			sign = -1;
		else
			sign = 1;
	}
	else
		sign = 1;
	return (to_int(str, sign));
}
