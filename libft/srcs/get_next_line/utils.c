/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsugiyam <tsugiyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 22:45:40 by tsugiyam          #+#    #+#             */
/*   Updated: 2021/05/11 22:45:40 by tsugiyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

void	renew_memory(char **memory, char *new)
{
	free(*memory);
	*memory = new;
}

int	add_memory(char **memory, char *left, char *right)
{
	char	*tmp;

	tmp = ft_strjoin(left, right);
	if (!tmp)
		return (-1);
	renew_memory(memory, tmp);
	return (1);
}
