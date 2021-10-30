/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serch_cmd_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnakahod <jnakahod@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 11:32:56 by jnakahod          #+#    #+#             */
/*   Updated: 2021/10/30 16:41:34 by jnakahod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

static void	replace_path(char **cmd, char *path)
{
	free(cmd[0]);
	cmd[0] = ft_strdup(path);
}

t_exit_cd	search_path(char **cmd)
{
	t_environ	*path;
	char		**paths;
	int			i;
	t_bool		deniedable;
	t_exit_cd	exit_cd;

	path = get_target_environ("PATH");
	paths = split_path(path->value, ':');
	i = -1;
	deniedable = FALSE;
	while (paths[++i])
	{
		paths[i] = add_slash(paths[i]);
		paths[i] = join_path(paths[i], cmd[0]);
		exit_cd = check_executable_cmd_path(paths[i], NULL);
		if (!deniedable && exit_cd == DENIED)
			deniedable = TRUE;
		if (exit_cd != SCCSS)
			continue;
		replace_path((char **)cmd, paths[i]);
		break;
	}
	multi_free(paths);
	if (exit_cd != SCCSS && deniedable)
		exit_cd = DENIED;
	return (exit_cd);
}
