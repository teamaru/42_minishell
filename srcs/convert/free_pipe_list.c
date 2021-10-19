/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_pipe_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnakahod <jnakahod@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 16:54:04 by jnakahod          #+#    #+#             */
/*   Updated: 2021/10/19 15:33:07 by jnakahod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

void	free_pipe_list(t_pipe_list *list)
{
	t_pipe_list	*next;
	t_pipe_list	*tmp;

	tmp = list;
	next = list->next;
	while (tmp)
	{
		free_pipe_node(&tmp);
		free_set((void **)&tmp, NULL);
		tmp = next;
		if (next || tmp)
			next = tmp->next;
	}
}
