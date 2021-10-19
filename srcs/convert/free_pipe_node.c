/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_pipe_node.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnakahod <jnakahod@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 15:31:00 by jnakahod          #+#    #+#             */
/*   Updated: 2021/10/19 15:34:15 by jnakahod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

void	free_cmd_args(const char **args)
{
	int	i;

	i = -1;
	if (!args)
		return ;
	while (args[++i])
		free_set((void **)&args[i], NULL);
}

void	free_demi_for_heredoc(t_demi_for_heredoc **demi_heredoc)
{
	if (*demi_heredoc)
	{
		free_set((void **)&(*demi_heredoc)->delimiter, NULL);
		free_set((void **)demi_heredoc, NULL);
	}
}

void	free_rd_list(t_redirection_list **rd_list)
{
	t_redirection_list	*tmp;
	t_redirection_list	*next;

	if (!(*rd_list))
		return ;
	tmp = (*rd_list);
	next = tmp->next;
	while (tmp)
	{
		if (tmp->file_path)
			free_set((void **)&tmp->file_path, NULL);
		else
			free_demi_for_heredoc(&tmp->demi_heredoc);
		free_set((void **)&tmp, NULL);
		tmp = next;
		if (next || tmp)
			next = tmp->next;
	}
}

void	free_heredoc_to_fd(t_heredoc_to_fd **heredoc)
{
	if (!*heredoc)
		return ;
	free_set((void **)&(*heredoc)->contents, NULL);
	free_set((void **)&(*heredoc)->tmp_file_path, NULL);
	free_set((void **)heredoc, NULL);
}

void	free_pipe_node(t_pipe_list **node)
{
	free_rd_list(&(*node)->output_rd);
	free_rd_list(&(*node)->input_rd);
	free_heredoc_to_fd(&(*node)->heredoc);
	free_cmd_args((*node)->cmd_args);
	free((*node)->cmd_args);
	(*node)->cmd_args = NULL;
	free_set((void **)&(*node)->heredoc, NULL);
}
