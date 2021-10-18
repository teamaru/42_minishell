/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_reference.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnakahod <jnakahod@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 22:08:39 by jnakahod          #+#    #+#             */
/*   Updated: 2021/10/12 11:47:03by jnakahod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

int	create_file_fd(char *file_path, int type, t_heredoc_to_fd *heredoc)
{
	int	file_fd;

	if (type == INPUT)
		file_fd = open(file_path, O_RDONLY);
	else if (type == OUTPUT)
		file_fd = open(file_path, O_RDWR | O_CREAT | O_TRUNC, 0666);
	else if (type == APPEND)
		file_fd = open(file_path, O_RDWR | O_CREAT | O_APPEND, 0666);
	else if (type == HEREDOC)
	{
		close(heredoc->tmp_fd);
		file_fd = open(heredoc->tmp_file_path, O_RDWR, 0666);
	}
	else
		file_fd = -1;
	if (file_fd < 0)
		perror("file_fd");
	return (file_fd);
}

int	change_reference(int std_fd, int file_fd)
{
	if (close(std_fd) < 0)
	{
		perror("close");
		return (-1);
	}
	if (dup2(file_fd, std_fd) < 0)
	{
		perror("dup2");
		close(file_fd);
		return (-1);
	}
	if (close(file_fd) < 0)
	{
		perror("close");
		return (-1);
	}
	return (0);
}

t_bool	is_last_heredoc(t_redirection_list *node)
{
	if (node->type == HEREDOC && node->demi_heredoc->last_heredoc)
		return (TRUE);
	return (FALSE);
}

t_bool	is_heredoc(t_redirection_list *node)
{
	if (node->type == HEREDOC)
		return (TRUE);
	return (FALSE);
}

int	change_multi_references(t_pipe_list *cmd)
{
	int					file_fd;
	t_redirection_list	*tmp;

	tmp = cmd->output_rd;
	while (tmp)
	{
		file_fd = create_file_fd(tmp->file_path, tmp->type, NULL);
		if (file_fd < 0)
			return (-1);
		if (change_reference(tmp->fd, file_fd) < 0)
			return (-1);
		tmp = tmp->next;
	}
	tmp = cmd->input_rd;
	while (tmp)
	{
		if (!is_heredoc(tmp) || is_last_heredoc(tmp))
		{
			file_fd = create_file_fd(tmp->file_path, tmp->type, cmd->heredoc);
			if (file_fd < 0)
				return (-1);
			if (change_reference(tmp->fd, file_fd) < 0)
				return (-1);
			if (cmd->heredoc && !access(cmd->heredoc->tmp_file_path, F_OK))
				unlink(cmd->heredoc->tmp_file_path);
		}
		tmp = tmp->next;
	}
	return (0);
}
