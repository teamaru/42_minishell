/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsugiyam <tsugiyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 12:58:43 by tsugiyam          #+#    #+#             */
/*   Updated: 2021/10/24 12:58:43 by tsugiyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

t_exit_cd return_or_exit(t_exit_cd exit_cd, t_bool is_child_process)
{
  if (is_child_process)
    exit(exit_cd);
  return (exit_cd);
}
char	*add_slash(char *cdpath)
{
	char	*tmp;

	if (cdpath[ft_strlen(cdpath) - 1] == SLSH)
		return (cdpath);
	tmp = cdpath;
	cdpath = ft_strjoin(cdpath, "/");
	free(tmp);
	return (cdpath);
}

char	*join_path(char *cdpath, char *path)
{
	char	*tmp;

	tmp = cdpath;
	cdpath = ft_strjoin(cdpath, path);
	free(tmp);
	return (cdpath);
}

t_bool	is_current_dir_exist(char *pwd)
{
	struct stat	stat_buf;

	return (lstat(pwd, &stat_buf) == 0);
}
