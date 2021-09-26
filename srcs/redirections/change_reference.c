/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_reference.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnakahod <jnakahod@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 22:08:39 by jnakahod          #+#    #+#             */
/*   Updated: 2021/09/26 14:08:49 by jnakahod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <redirect.h>

int create_file_fd(char *file_path, int type)
{
	int file_fd;

	if (type == INPUT)
		file_fd = open(file_path, O_RDONLY);
	else if (type == OUTPUT)
		file_fd = open(file_path, O_RDWR | O_CREAT | O_TRUNC, 0666);
	else if (type == APPEND)
		file_fd = open(file_path, O_RDWR | O_CREAT | O_APPEND, 0666);
	else
		file_fd = -1;
	// else if (type == HEREDOC)
	if (file_fd < 0)
		perror(file_path);
	return (file_fd);
}

int change_reference(int std_fd, int file_fd)
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

int change_multi_references(t_complete_cmd *cmd)
{
	int file_fd;
	t_redirection_list *tmp;

	tmp = cmd->output_rd;
	while (tmp)
	{
		file_fd = create_file_fd(tmp->file_path, tmp->type);
		if (file_fd < 0)
			return (-1);
		if (change_reference(tmp->fd, file_fd) < 0)
			return (-1);
		tmp = tmp->next;
	}
	tmp = cmd->input_rd;
	while (tmp)
	{
		file_fd = create_file_fd(tmp->file_path, tmp->type);
		if (file_fd < 0)
			return (-1);
		if (change_reference(tmp->fd, file_fd) < 0)
			return (-1);
		tmp = tmp->next;
	}
	return (0);
}
