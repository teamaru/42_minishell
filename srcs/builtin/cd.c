/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsugiyam <tsugiyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 23:21:06 by tsugiyam          #+#    #+#             */
/*   Updated: 2021/11/02 21:40:18 by tsugiyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

extern t_request	g_request;

t_bool	is_current_dir_exist(void)
{
	char		pwd[BUFSIZ];
	struct stat	stat_buf;

	getcwd(pwd, BUFSIZ);
	return (lstat(pwd, &stat_buf) == 0);
}

t_bool	search_cdpath(char *path)
{
	t_environ	*cdpath;
	char		**cdpaths;
	int			i;

	cdpath = get_target_environ("CDPATH");
	if (!cdpath)
		return (FALSE);
	cdpaths = ft_split(cdpath->value, ':');
	i = -1;
	while (cdpaths[++i])
	{
		cdpaths[i] = add_slash(cdpaths[i]);
		cdpaths[i] = join_path(cdpaths[i], path);
		if (chdir(cdpaths[i]) == -1)
			continue ;
		renew_pwd(cdpaths[i]);
		print_pwd();
		multi_free(cdpaths);
		return (TRUE);
	}
	multi_free(cdpaths);
	return (FALSE);
}

t_bool	set_home_dir(char **path)
{
	t_environ	*home;

	home = get_target_environ("HOME");
	if (!home)
		return (FALSE);
	*path = home->value;
	return (TRUE);
}

t_exit_cd	execute_cd(const char **cmd_args, t_bool is_child_process)
{
	char	*path;
	t_bool	is_changed;

	is_changed = FALSE;
	replace_oldpwd();
	path = (char *)cmd_args[1];
	if (!path && !set_home_dir(&path))
		return (builtin_err(ERR_MSG_HOME_NOT_SET,
				GNRL_ERR, is_child_process));
	if (!path || !*path)
		return (return_or_exit(SCCSS, is_child_process));
	if (*path == PERIOD && !is_current_dir_exist())
	{
		renew_pwd(path);
		return (builtin_err(ERR_MSG_NO_FILE, GNRL_ERR, is_child_process));
	}
	if (is_path_part(path))
		is_changed = search_cdpath(path);
	if (is_changed)
		return (return_or_exit(SCCSS, is_child_process));
	if (chdir(path) == -1)
		return (builtin_err(NULL, GNRL_ERR, is_child_process));
	renew_pwd(path);
	return (return_or_exit(SCCSS, is_child_process));
}
