/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_reference.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnakahod <jnakahod@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 22:08:39 by jnakahod          #+#    #+#             */
/*   Updated: 2021/11/06 14:00:05 by jnakahod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

void	fail_open_set_err(char *file_path, int file_fd, char **err_msg)
{
	struct stat	buf;

	if (file_fd >= 0)
		return ;
	free_set((void **)err_msg, ft_strdup(ERR_MSG_NO_FILE));
	stat(file_path, &buf);
	if (!file_path || !*file_path)
		free_set((void **)err_msg, ft_strdup(ERR_MSG_AMBGS_RDRCT));
	else if (S_ISDIR(buf.st_mode))
		free_set((void **)err_msg, ft_strdup(ERR_MSG_IS_DIR));
}

int	create_file_fd(char *file_path, int type,
	t_heredoc_to_fd *heredoc, char **err_msg)
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
	fail_open_set_err(file_path, file_fd, err_msg);
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

t_result	change_single_reference(int *file_fd, t_redirection_list *tmp,
	t_heredoc_to_fd *heredoc, char **err_msg)
{
	*file_fd = create_file_fd(tmp->file_path, tmp->type, heredoc, err_msg);
	if (*file_fd < 0)
		return (FAILURE);
	if (change_reference(tmp->fd, *file_fd) < 0)
		return (FAILURE);
	return (SUCCESS);
}

int	change_multi_references(t_pipe_list *cmd, char **err_msg)
{
	int					file_fd;
	t_redirection_list	*tmp;

	tmp = cmd->output_rd;
	while (tmp)
	{
		if (change_single_reference(&file_fd, tmp, NULL, err_msg) == FAILURE)
			return (-1);
		tmp = tmp->next;
	}
	tmp = cmd->input_rd;
	while (tmp)
	{
		if (!is_heredoc(tmp) || is_last_heredoc(tmp))
		{
			if (change_single_reference(&file_fd, tmp,
					cmd->heredoc, err_msg) == FAILURE)
				return (-1);
			if (is_last_heredoc(tmp)
				&& !access(cmd->heredoc->tmp_file_path, F_OK))
				unlink(cmd->heredoc->tmp_file_path);
		}
		tmp = tmp->next;
	}
	return (0);
}
