/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsugiyam <tsugiyam@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 16:59:45 by tsugiyam          #+#    #+#             */
/*   Updated: 2021/11/09 12:35:37 by tsugiyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "./libft.h"

void	ft_putchar_fd(char c, int fd)
{
	unsigned char	uc_c;

	uc_c = (unsigned char)c;
	write(fd, &uc_c, 1);
	return ;
}
