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

void	init_heredoc(t_heredoc_to_fd **heredoc)
{
	*heredoc = (t_heredoc_to_fd *)ft_calloc(1, sizeof(t_heredoc_to_fd));
	(*heredoc)->contents = NULL;
	(*heredoc)->tmp_fd = -1;
	(*heredoc)->tmp_file_path = NULL;
}

void	set_heredocument(t_pipe_list **node, t_heredoc_to_fd **heredoc)
{
	t_redirection_list	*tmp_input;
	t_demi_for_heredoc	*tmp_demi;

	if (!(*node) || !(*node)->input_rd)
		return ;
	tmp_demi = NULL;
	tmp_input = (*node)->input_rd;
	while (tmp_input)
	{
		if (tmp_input->type == HEREDOC)
		{
			if (!(*heredoc))
				init_heredoc(heredoc);
			tmp_demi = tmp_input->demi_heredoc;
			form_heredocument(tmp_demi->delimiter, &(*heredoc)->contents);
		}
		tmp_input = tmp_input->next;
	}
	if (tmp_demi)
		tmp_demi->last_heredoc = TRUE;
}
