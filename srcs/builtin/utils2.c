/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsugiyam <tsugiyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 11:21:47 by tsugiyam          #+#    #+#             */
/*   Updated: 2021/11/09 12:34:18 by tsugiyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

extern t_request	g_request;

t_bool	is_path_exist(char *path)
{
	struct stat	stat_buf;

	return (lstat(path, &stat_buf) == 0);
}

t_bool	is_current_dir_exist(void)
{
	char		pwd[BUFSIZ];
	struct stat	stat_buf;

	getcwd(pwd, BUFSIZ);
	return (lstat(pwd, &stat_buf) == 0);
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

t_bool	is_end_slash(char *str)
{
	if (!str)
		return (FALSE);
	return (str[ft_strlen(str) - 1] == '/');
}

void	replace_pwd(char **split, t_bool flg)
{
	int	i;

	i = -1;
	if (flg)
		free_pwd(&g_request.pwd);
	while (split[++i])
		append_pwd(&g_request.pwd, new_pwd(ft_strdup(split[i]), FALSE));
}
