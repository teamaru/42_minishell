/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serch_cmd_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnakahod <jnakahod@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 11:32:56 by jnakahod          #+#    #+#             */
/*   Updated: 2021/10/19 15:23:09 by jnakahod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

static void	replace_path(char **cmd, char *path)
{
	free(cmd[0]);
	cmd[0] = ft_strdup(path);
}

t_bool	search_path(char **cmd)
{
	t_environ	*path;
	char		**paths;
	int			i;

	path = get_target_environ("PATH");
	paths = ft_split(path->value, ':');
	i = -1;
	while (paths[++i])
	{
		paths[i] = add_slash(paths[i]);
		paths[i] = join_path(paths[i], cmd[0]);
		if (access(paths[i], F_OK) == -1)
			continue ;
		replace_path(cmd, paths[i]);
		multi_free(paths);
		return (TRUE);
	}
	multi_free(paths);
	return (FALSE);
}
