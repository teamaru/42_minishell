/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_pipe_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnakahod <jnakahod@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 16:54:04 by jnakahod          #+#    #+#             */
/*   Updated: 2021/09/27 16:55:04 by jnakahod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>
#include <convert.h>

static void	free_set(void **dst, void *src)
{
	free(*dst);
	*dst = src;
}

void	free_pipe_node(t_pipe_list **node)
{
	const char	**args;
	int			i;

	args = (*node)->cmd_args;
	i = -1;
	while (args[++i])
		free_set((void **)&args[i], NULL);
	free(args);
	args = NULL;
}

void	free_pipe_list(t_pipe_list *list)
{
	t_pipe_list	*next;
	t_pipe_list	*tmp;

	tmp = list;
	next = list->next;
	//free処理
	while (!tmp)
	{
		free_pipe_node(&tmp);
		free_set((void **)&tmp, NULL);
		tmp = next;
		if (next || tmp)
			next = tmp->next;
	}
}
