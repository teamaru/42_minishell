/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnakahod <jnakahod@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 22:30:32 by jnakahod          #+#    #+#             */
/*   Updated: 2021/09/17 21:08:09 by jnakahod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./redirect.h"
#include "../../libft/includes/libft.h"
#include <fcntl.h>

/*
** comamnd < file_path
*/
void	redirecting_input(char *file_path)
{
	int		file_fd;

	// ファイルをオープンしfdを得る
	file_fd = open(file_path, O_RDONLY);
	if (file_fd < 0)
	{
		perror("open");
		exit(1);
	}
	// 標準入力(fd=0)をクローズする
	if (close(0) < 0)
	{
		perror("close");
		exit(1);
	}
	// dup2でfile_fdの複製をfd=0として作成する
	if (dup2(file_fd, 0) <  0)
	{
		perror("dup2");
		close(file_fd);
		exit(1);
	}
	// file_fdをクローズしファイルはfd=0からのみアクセス可能
	if (close(file_fd) < 0)
	{
		perror("close");
		exit(1);
	}
}
