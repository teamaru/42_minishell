/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_tmp_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnakahod <jnakahod@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 14:22:57 by jnakahod          #+#    #+#             */
/*   Updated: 2021/10/19 16:09:09 by jnakahod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

char	*get_tmp_file_path(int i)
{
	char	*num;
	char	*file_path;

	num = ft_itoa(i);
	if (!*num)
		return (NULL);
	file_path = ft_strjoin(TMPFILE, num);
	free(num);
	return (file_path);
}

t_result	heredoc_to_fd(t_heredoc_to_fd *heredoc)
{
	char		*contents;
	static int	i = -1;

	heredoc->tmp_file_path = get_tmp_file_path(++i);
	if (!heredoc->tmp_file_path)
		return (FAILURE);
	heredoc->tmp_fd = open(heredoc->tmp_file_path,
			O_RDWR | O_CREAT | O_EXCL, 0666);
	if (heredoc->tmp_fd < 0)
		return (FAILURE);
	contents = heredoc->contents;
	if (write(heredoc->tmp_fd, contents, ft_strlen(contents)) < 0)
	{
		close_and_unlink(&heredoc, TRUE);
		return (FAILURE);
	}
	return (SUCCESS);
}

t_result	write_heredoc(t_heredoc_to_fd *heredoc)
{
	if (!has_heredoc(heredoc))
		return (SUCCESS);
	heredoc_to_fd(heredoc);
	if (heredoc->tmp_fd < 0)
		return (FAILURE);
	else
		return (SUCCESS);
}
