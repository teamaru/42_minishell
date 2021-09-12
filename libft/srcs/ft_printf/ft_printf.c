/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsugiyam <tsugiyam@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 12:54:58 by tsugiyam          #+#    #+#             */
/*   Updated: 2021/05/11 18:52:51 by tsugiyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "./libft.h"

void	init_format(t_format *input)
{
	input->flgs[MINUS] = 0;
	input->flgs[ZERO] = 0;
	input->field = -1;
	input->accuracy = -1;
	input->specifier = -1;
	input->output_size = 0;
}

int	ft_check_format(const char **format, t_format *input, va_list args)
{
	(*format)++;
	ft_check_flg(format, input);
	if (!ft_check_field_accuracy(format, input, args, FLD))
		return (0);
	ft_check_period(format, input);
	if (!ft_check_field_accuracy(format, input, args, ACC))
		return (0);
	ft_check_specifier(format, input);
	return (1);
}

int	ft_put_format(va_list args, t_format *input)
{
	if (!input->specifier)
		return (-1);
	if (input->specifier == 'c')
		ft_putchar(input, va_arg(args, int));
	if (input->specifier == 's')
		ft_putstr(input, va_arg(args, char *));
	if (input->specifier == 'd' || input->specifier == 'i')
		ft_putnbr(input, ft_itoa(va_arg(args, int)));
	if (input->specifier == 'p')
		ft_put_addr(input, va_arg(args, void *));
	if (input->specifier == 'u')
		ft_putnbr(input, convert_base(va_arg(args, unsigned int), DEC));
	if (input->specifier == 'x')
		ft_putnbr(input, convert_base(va_arg(args, unsigned int), L_HEX));
	if (input->specifier == 'X')
		ft_putnbr(input, convert_base(va_arg(args, unsigned int), U_HEX));
	if (input->specifier == '%')
		ft_putchar(input, '%');
	return (input->output_size);
}

int	ft_print_format(const char *format, va_list args, t_format *input)
{
	int			cnt;
	int			output_cnt;

	output_cnt = 0;
	while (*format)
	{
		init_format(input);
		output_cnt += ft_put_non_format(&format);
		if (!*format)
			break ;
		if (!ft_check_format(&format, input, args))
			return (-1);
		cnt = ft_put_format(args, input);
		if (cnt == -1)
			return (-1);
		output_cnt += cnt;
	}
	return (output_cnt);
}

int	ft_printf(const char *format, ...)
{
	int			output_cnt;
	va_list		args;
	t_format	*input;

	if (!format)
		return (-1);
	va_start(args, format);
	input = malloc(sizeof(t_format));
	if (!input)
		return (-1);
	output_cnt = ft_print_format(format, args, input);
	free(input);
	va_end(args);
	return (output_cnt);
}
