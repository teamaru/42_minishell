/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsugiyam <tsugiyam@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 12:58:44 by tsugiyam          #+#    #+#             */
/*   Updated: 2021/05/11 21:45:27 by tsugiyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

int	ft_put_non_format(const char **format)
{
	int	cnt;

	cnt = 0;
	while ((*format)[cnt] && (*format)[cnt] != '%')
		ft_putchar_fd((*format)[cnt++], 1);
	*format += cnt;
	return (cnt);
}

void	ft_putchar(t_format *input, char c)
{
	input->output_size++;
	input->output_size += ft_put_padding(input, PRE);
	ft_putchar_fd(c, 1);
	input->output_size += ft_put_padding(input, SUF);
}

void	ft_putstr(t_format *input, char *s)
{
	int	no_acc;

	if (!s)
		s = "(null)";
	no_acc = input->accuracy == -1;
	if (no_acc)
		input->output_size += ft_strlen(s);
	else
		input->output_size += ft_cmp(ft_strlen(s), input->accuracy, MIN);
	input->output_size += ft_put_padding(input, PRE);
	if (no_acc)
		ft_putstr_fd(s, 1);
	else
		ft_putstr_n(s, input->accuracy);
	input->output_size += ft_put_padding(input, SUF);
}

void	ft_put_addr(t_format *input, void *addr)
{
	int		nbr_size;
	char	*hex_addr;

	hex_addr = convert_base((unsigned long)addr, L_HEX);
	if (*hex_addr == '0' && input->accuracy == 0)
	{
		free(hex_addr);
		hex_addr = NULL;
	}
	nbr_size = ft_strlen(hex_addr);
	input->output_size += ft_cmp(nbr_size, input->accuracy, MAX) + 2;
	input->output_size += ft_put_padding(input, PRE);
	ft_putstr_fd("0x", 1);
	ft_put_accuracy(input, nbr_size, 0);
	ft_putstr_fd(hex_addr, 1);
	input->output_size += ft_put_padding(input, SUF);
	free(hex_addr);
}

void	ft_putnbr(t_format *input, char *nbr)
{
	int		is_neg;
	int		nbr_size;

	if (*nbr == '-')
		is_neg = 1;
	else
		is_neg = 0;
	if (is_neg)
		remove_minus(&nbr);
	if (*nbr == '0' && input->accuracy == 0)
		nbr = NULL;
	nbr_size = ft_strlen(nbr);
	input->output_size += ft_cmp(nbr_size,
			input->accuracy, MAX) + is_neg;
	if (is_neg && input->flgs[ZERO])
		is_neg = ft_put_minus();
	input->output_size += ft_put_padding(input, PRE);
	is_neg = ft_put_accuracy(input, nbr_size, is_neg);
	if (is_neg)
		is_neg = ft_put_minus();
	ft_putstr_fd(nbr, 1);
	input->output_size += ft_put_padding(input, SUF);
	free(nbr);
}
