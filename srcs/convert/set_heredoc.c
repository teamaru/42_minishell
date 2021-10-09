/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnakahod <jnakahod@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 23:50:02 by jnakahod          #+#    #+#             */
/*   Updated: 2021/10/09 15:33:25by jnakahod         ###   ########.fr       */
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

char	*update_heredoc(char **old, char *input)
{
	char	*joined_input;
	char	*new_heredoc;

	joined_input = NULL;
	new_heredoc = NULL;
	joined_input = ft_strjoin(*old, input);
	free_set((void **)old, NULL);
	if (!joined_input)
		return (NULL);
	new_heredoc = ft_strjoin(joined_input, "\n");
	free_set((void **)&joined_input, NULL);
	if (!new_heredoc)
		return (NULL);
	return (new_heredoc);
}

char	*readline_input_heredoc(char **delimiters)
{
	char	*heredoc;
	char	*input;

	heredoc = NULL;
	input = NULL;
	while (1)
	{
		input = readline("> ");
		if (!input)
			break;
		heredoc = update_heredoc(&heredoc, input);
		free_set((void **)&input, NULL);
	}
	return (heredoc);
}

void	set_heredocument(t_pipe_list **node)
{
	t_demi_for_heredoc	*last_demi;
	int					size_of_delimiters;
	char				**delimiters;
	// t_bool				expantable_heredoc;

	if (!(*node))
		return ;
	size_of_delimiters = 0;
	last_demi = NULL;
	size_of_delimiters = count_size_of_delimiters((*node)->input_rd, &last_demi);
	if (!size_of_delimiters)
		return ;
	// expantable_heredoc = is_last_delimiter_has_quarts(last_demi->delimiter);
	delimiters = create_delimiters_array((*node)->input_rd, size_of_delimiters);
	(*node)->heredoc = readline_input_heredoc(delimiters);
	free_delimiters(&delimiters, size_of_delimiters);
}
