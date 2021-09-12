/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   padding.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsugiyam <tsugiyam@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 13:00:03 by tsugiyam          #+#    #+#             */
/*   Updated: 2021/05/11 21:47:29 by tsugiyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

int	ft_put_accuracy(t_format *input, int nbr_size, int is_neg)
{
	while (input->accuracy-- > nbr_size)
	{
		if (is_neg)
			is_neg = ft_put_minus();
		ft_putchar_fd('0', 1);
	}
	return (is_neg);
}

int	ft_padding(t_format *input)
{
	int	cnt;

	cnt = 0;
	while (input->field - cnt++ > input->output_size)
	{
		if (input->flgs[ZERO])
			ft_putchar_fd('0', 1);
		else
			ft_putchar_fd(' ', 1);
	}
	return (cnt - 1);
}

int	ft_put_padding(t_format *input, t_toggle toggle)
{
	if (!input->flgs[MINUS] && toggle == PRE)
		return (ft_padding(input));
	if (input->flgs[MINUS] && toggle == SUF)
		return (ft_padding(input));
	return (0);
}

int	ft_put_minus(void)
{
	ft_putchar_fd('-', 1);
	return (0);
}

void	remove_minus(char **nbr)
{
	char	*tmp;

	tmp = ft_strdup(*nbr + 1);
	free(*nbr);
	*nbr = tmp;
}
