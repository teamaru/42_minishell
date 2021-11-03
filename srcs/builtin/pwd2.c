/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsugiyam <tsugiyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 21:25:06 by tsugiyam          #+#    #+#             */
/*   Updated: 2021/11/02 21:38:27 by tsugiyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

extern t_request	g_request;

void	replace_oldpwd(void)
{
	t_environ	*pwd_env;
	char		*pwd;

	pwd_env = get_target_environ("PWD");
	if (pwd_env)
		pwd = pwd_env->value;
	else
		pwd = NULL;
	free(g_request.oldpwd);
	g_request.oldpwd = ft_strdup(pwd);
	replace_env_value("OLDPWD", pwd);
}

void	normalize_pwd(void)
{
	t_pwd	*pwd;
	t_pwd	*next;

	pwd = g_request.pwd;
	while (pwd)
	{
		if (!ft_strcmp(pwd->dir, ".."))
			delete_pwd(&g_request.pwd, pwd->prev);
		free_set((void **)&pwd->dir, ft_strtrim(pwd->dir, "."));
		if (!pwd->dir || !ft_strcmp(pwd->dir, ""))
		{
			next = pwd->next;
			delete_pwd(&g_request.pwd, pwd);
			pwd = next;
			continue ;
		}
		if (pwd)
			pwd = pwd->next;
	}
}

void	replace_pwd(char **split, t_bool flg)
{
	int	i;

	i = -1;
	if (flg)
		free_pwd(&g_request.pwd);
	while (split[++i])
		append_pwd(&g_request.pwd, new_pwd(ft_strdup(split[i])));
}

char	*stringify_pwd(void)
{
	t_pwd	*pwd;
	char	*str_pwd;

	pwd = g_request.pwd;
	str_pwd = NULL;
	while (pwd)
	{
		free_set((void **)&str_pwd, ft_strjoin(str_pwd, "/"));
		free_set((void **)&str_pwd, ft_strjoin(str_pwd, pwd->dir));
		pwd = pwd->next;
	}
	return (str_pwd);
}

void	renew_pwd(char *path)
{
	char	*str_pwd;
	char	**split;

	if (!is_current_dir_exist())
		append_pwd(&g_request.pwd, new_pwd(ft_strdup(path)));
	else
	{
		split = ft_split(path, '/');
		if (path[0] == '/')
			replace_pwd(split, TRUE);
		else
			replace_pwd(split, FALSE);
		normalize_pwd();
		multi_free(split);
	}
	str_pwd = stringify_pwd();
	replace_env_value("PWD", str_pwd);
	free(str_pwd);
}
