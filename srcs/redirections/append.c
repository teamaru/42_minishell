/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnakahod <jnakahod@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 17:02:23 by jnakahod          #+#    #+#             */
/*   Updated: 2021/09/17 19:09:40 by jnakahod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <redirect.h>

/*
** >> の特徴
** fileが存在しなければ新しく作成する
*/
void	redirecting_append(char *file_path)
{
	int	file_fd;

	file_fd = open(file_path, O_RDWR | O_CREAT | O_APPEND, 0666);
	if (file_fd < 0)
	{
		perror(file_path);
		exit(1);
	}
	if (close(1) < 0)
	{
		perror("close");
		exit(1);
	}
	if (dup2(file_fd, 1) < 0)
	{
		perror("dup");
		close(file_fd);
		exit(1);
	}
	if (close(file_fd) < 0)
	{
		perror("close");
		exit(1);
	}
}
