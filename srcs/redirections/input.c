/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnakahod <jnakahod@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 22:30:32 by jnakahod          #+#    #+#             */
/*   Updated: 2021/09/16 21:02:21 by jnakahod         ###   ########.fr       */
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
	close(0);

	// dup2でfile_fdの複製をfd=0として作成する
	if (dup2(file_fd, 0) <  0)
	{
		perror("dup2");
		close(file_fd);
		exit(1);
	}

	// file_fdをクローズしファイルはfd=0からのみアクセス可能
	close(file_fd);
}
