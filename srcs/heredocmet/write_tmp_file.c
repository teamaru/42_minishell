/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_tmp_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnakahod <jnakahod@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 14:22:57 by jnakahod          #+#    #+#             */
/*   Updated: 2021/10/18 14:26:54 by jnakahod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

char *get_tmp_file_path(int i)
{
	char *num;
	char *file_path;

	num = ft_itoa(i);
	if (!*num)
		return (NULL);
	file_path = ft_strjoin(TMPFILE, num);
	free(num);
	return (file_path);
}

int heredoc_to_fd(t_heredoc_to_fd *heredoc)
{
	int tmp_file_fd;
	char *contents;
	static int i = -1;

	heredoc->tmp_file_path = get_tmp_file_path(++i);
	if (!heredoc->tmp_file_path)
		return (-1);
	tmp_file_fd = open(heredoc->tmp_file_path, O_RDWR | O_CREAT | O_EXCL, 0666);
	if (tmp_file_fd < 0)
		return (-1);
	contents = heredoc->contents;
	if (write(tmp_file_fd, contents, ft_strlen(contents)) < 0)
	{
		close(tmp_file_fd);
		unlink(heredoc->tmp_file_path);
		return (-1);
	}
	return (tmp_file_fd);
}

t_result write_heredoc(t_heredoc_to_fd *heredoc)
{
	if (!has_heredoc(heredoc))
		return (SUCCESS);
	heredoc->tmp_fd = heredoc_to_fd(heredoc);
	if (heredoc->tmp_fd < 0)
		return (FAILURE);
	else
		return (SUCCESS);
}
