/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnakahod <jnakahod@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 23:50:02 by jnakahod          #+#    #+#             */
/*   Updated: 2021/10/09 14:28:28 by jnakahod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

static void	free_set(void **dst, void *src)
{
	free(*dst);
	*dst = src;
}

int count_size_of_delimiters(t_redirection_list *node, t_demi_for_heredoc **last_demi_heredoc)
{
	t_redirection_list *tmp;
	int					size_delimiters;

	tmp = node;
	size_delimiters = 0;
	while (tmp)
	{
		if (tmp->type == HEREDOC)
		{
			size_delimiters++;
			*last_demi_heredoc = tmp->demi_heredoc;
		}
		tmp = tmp->next;
	}
	return (size_delimiters);
}

void	*free_delimiters(char ***delimiters, int size)
{
	int	i;

	i = -1;
	while (++i < size)
		free_set((void **)&(*delimiters)[i], NULL);
	free(*delimiters);
	*delimiters = NULL;
	return (NULL);
}

char	**create_delimiters_array(t_redirection_list *rd_list, int size_array)
{
	char				**delimiters;
	int					i;
	t_redirection_list	*tmp;

	delimiters = (char **)malloc(sizeof(char *) * (size_array + 1));
	if (!delimiters)
		return (NULL);
	tmp = rd_list;
	i = 0;
	while (tmp)
	{
		if (tmp->type == HEREDOC)
		{
			delimiters[i] = ft_strdup(tmp->demi_heredoc->delimiter);
			if (!delimiters[i])
				return (free_delimiters(&delimiters, i));
			i++;
		}
		tmp = tmp->next;
	}
	delimiters[i] = NULL;
	return (delimiters);
}

void	set_heredocument(t_pipe_list **node)
{
	t_redirection_list	*tmp;
	t_demi_for_heredoc	*last_demi_node;
	int					size_of_delimiters;
	char				**delimiters;

	size_of_delimiters = 0;
	last_demi_node = NULL;
	size_of_delimiters = count_size_of_delimiters((*node)->input_rd, &last_demi_node);
	if (last_demi_node)
		last_demi_node->last_heredoc = TRUE;
	delimiters = create_delimiters_array((*node)->input_rd, size_of_delimiters);
	//readlineでheredoc作成
	// return (SUCCESS);
}
