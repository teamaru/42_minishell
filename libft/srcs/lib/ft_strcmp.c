/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsugiyam <tsugiyam@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 13:01:50 by tsugiyam          #+#    #+#             */
/*   Updated: 2021/03/02 13:01:53 by tsugiyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned char	*uc_s1;
	unsigned char	*uc_s2;
	size_t			i;

	i = 0;
	uc_s1 = (unsigned char *)s1;
	uc_s2 = (unsigned char *)s2;
	while (uc_s1[i] && uc_s1[i] == uc_s2[i])
		i++;
	return (uc_s1[i] - uc_s2[i]);
}
