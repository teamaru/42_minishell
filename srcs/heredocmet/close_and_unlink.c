/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_and_unlink.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnakahod <jnakahod@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 14:34:52 by jnakahod          #+#    #+#             */
/*   Updated: 2021/10/18 14:42:41 by jnakahod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

void	close_and_unlink(t_heredoc_to_fd **heredoc, t_bool	unlinkable)
{
	if (has_heredoc(*heredoc))
	{
		close((*heredoc)->tmp_fd);
		if (unlinkable)
			unlink((*heredoc)->tmp_file_path);
	}
}
