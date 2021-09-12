/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsugiyam <tsugiyam@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 17:00:23 by tsugiyam          #+#    #+#             */
/*   Updated: 2021/05/11 22:28:12 by tsugiyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "./libft.h"

static void	recursive_putnbr(unsigned int ui_n, int fd)
{
	if (ui_n == 0)
		return ;
	recursive_putnbr(ui_n / 10, fd);
	ft_putchar_fd(ui_n % 10 + '0', 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	ui_n;

	if (n < 0)
		write(fd, "-", 1);
	if (n < 0)
		ui_n = -n;
	else
		ui_n = n;
	recursive_putnbr(ui_n, fd);
	if (n == 0)
		write(fd, "0", 1);
}
