/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsugiyam <tsugiyam@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 17:09:36 by tsugiyam          #+#    #+#             */
/*   Updated: 2021/05/11 22:42:24 by tsugiyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

int	ft_toupper(int c)
{
	if ('a' <= c && c <= 'z')
		return ((c - ('a' - 'A')));
	else
		return (c);
}
