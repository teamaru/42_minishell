/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsugiyam <tsugiyam@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 12:57:56 by tsugiyam          #+#    #+#             */
/*   Updated: 2021/05/11 18:57:12 by tsugiyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

void	ft_check_flg(const char **format, t_format *input)
{
	int	i;

	i = ft_strchr_i(FLAGS, **format);
	while (i != -1)
	{
		i = ft_strchr_i(FLAGS, **format);
		input->flgs[i] = 1;
		(*format)++;
	}
	if (input->flgs[MINUS])
		input->flgs[ZERO] = 0;
}

int	ft_check_aster(const char **format,
		t_format *input, va_list args, t_toggle toggle)
{
	int	tmp;

	if (**format == '*')
	{
		(*format)++;
		tmp = va_arg(args, int);
		if (tmp < 0 && toggle == FLD)
		{
			tmp *= -1;
			input->flgs[MINUS] = 1;
			input->flgs[ZERO] = 0;
		}
		else if (tmp < 0 && toggle == ACC)
			tmp = -1;
		if (toggle == FLD)
			input->field = tmp;
		else
			input->accuracy = tmp;
		if (input->field == INT_MAX)
			return (0);
	}
	return (1);
}

int	ft_check_field_accuracy(const char **format,
								t_format *input, va_list args, t_toggle toggle)
{
	int		i;
	char	*tmp;

	if (!ft_check_aster(format, input, args, toggle))
		return (0);
	i = 0;
	while (ft_isdigit((*format)[i]))
		i++;
	if (i == 0)
		return (1);
	tmp = ft_substr(*format, 0, i);
	if (!tmp)
		return (0);
	if (toggle == FLD)
		input->field = ft_atoi(tmp);
	else
		input->accuracy = ft_atoi(tmp);
	free(tmp);
	if (input->field == INT_MAX)
		return (0);
	*format += i;
	return (1);
}

void	ft_check_period(const char **format, t_format *input)
{
	if (**format == '.')
	{
		if (!ft_isdigit(*(*format + 1)))
			input->accuracy = 0;
		input->flgs[ZERO] = 0;
		(*format)++;
	}
}

void	ft_check_specifier(const char **format, t_format *input)
{
	int	i;

	i = ft_strchr_i(SPECS, **format);
	if (i != -1)
	{
		input->specifier = SPECS[i];
		(*format)++;
	}
}
