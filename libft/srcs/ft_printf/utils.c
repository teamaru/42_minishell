/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsugiyam <tsugiyam@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 13:00:33 by tsugiyam          #+#    #+#             */
/*   Updated: 2021/05/11 21:51:54 by tsugiyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

void	ft_putstr_n(const char *s, int n)
{
	if (n < 0)
		return ;
	while (*s && n--)
		ft_putchar_fd(*s++, 1);
}

int	ft_cmp(int nbr1, int nbr2, t_cmp cmp)
{
	if (cmp == MAX)
	{
		if (nbr1 > nbr2)
			return (nbr1);
		else
			return (nbr2);
	}
	else
	{
		if (nbr1 < nbr2)
			return (nbr1);
		else
			return (nbr2);
	}
}

int	get_nbr_size(unsigned long nbr, char *base)
{
	int	radix;
	int	size;

	radix = ft_strlen(base);
	size = 1;
	nbr /= radix;
	while (nbr)
	{
		nbr /= radix;
		size++;
	}
	return (size);
}

char	*convert_base(unsigned long src, char *base)
{
	int		size;
	int		radix;
	char	*res;

	size = get_nbr_size(src, base);
	res = malloc(size + 1);
	if (!res)
		return (NULL);
	res[size--] = 0;
	if (src == 0)
		res[0] = '0';
	radix = ft_strlen(base);
	while (src)
	{
		res[size--] = base[src % radix];
		src /= radix;
	}
	return (res);
}
