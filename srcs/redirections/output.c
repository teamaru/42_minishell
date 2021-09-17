/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnakahod <jnakahod@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 13:59:06 by jnakahod          #+#    #+#             */
/*   Updated: 2021/09/17 21:10:58 by jnakahod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <redirect.h>

/*
** command > file_path
*/
void	redirecting_output(char *file_path)
{
	int	file_fd;

	file_fd = open(file_path, O_RDWR | O_CREAT | O_TRUNC, S_IREAD | S_IWRITE);
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
	// file_fdの複製をfd=0として作成
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
