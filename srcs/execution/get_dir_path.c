/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_dir_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnakahod <jnakahod@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 16:25:15 by jnakahod          #+#    #+#             */
/*   Updated: 2021/10/30 17:00:50 by jnakahod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

char	*get_dir_path(const char *cmd_path)
{
	char	*dir_path;
	int		dir_path_size;
	size_t	i;

	i = 0;
	dir_path_size = 0;
	while (cmd_path[i])
	{
		if (cmd_path[i] == '/')
			dir_path_size = i;
		i += 1;
	}
	dir_path = (char *)ft_calloc((dir_path_size + 1), sizeof(char));
	if (!dir_path)
		return (NULL);
	ft_strlcpy(dir_path, cmd_path, dir_path_size + 1);
	return (dir_path);
}
