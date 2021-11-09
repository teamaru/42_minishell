/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsugiyam <tsugiyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 21:25:06 by tsugiyam          #+#    #+#             */
/*   Updated: 2021/11/09 12:33:22 by tsugiyam         ###   ########.fr       */
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

void	normalize_pwd(t_pwd **head)
{
	t_pwd	*pwd;
	t_pwd	*next;

	pwd = *head;
	while (pwd)
	{
		if (!ft_strcmp(pwd->dir, "..") || !ft_strcmp(pwd->dir, "../"))
			delete_pwd(&g_request.pwd, pwd->prev);
		free_set((void **)&pwd->dir, ft_strtrim(pwd->dir, "./"));
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

char	*stringify_pwd(t_pwd *head)
{
	t_pwd	*pwd;
	char	*str_pwd;

	pwd = head;
	str_pwd = NULL;
	free_set((void **)&str_pwd, ft_strjoin(str_pwd, "/"));
	while (pwd)
	{
		free_set((void **)&str_pwd, ft_strjoin(str_pwd, pwd->dir));
		if ((pwd->next && !pwd->is_preserve)
			|| (pwd->is_preserve && !is_end_slash(pwd->dir) && pwd->next))
			free_set((void **)&str_pwd, ft_strjoin(str_pwd, "/"));
		pwd = pwd->next;
	}
	return (str_pwd);
}

void	set_preserve_dir(char *path)
{
	int	i;

	i = 0;
	while (path && path[i])
	{
		while (path[i] && path[i] != '/')
			i++;
		if (path[i] == '/')
			i++;
		append_pwd(&g_request.pwd, new_pwd(ft_strndup(path, i), TRUE));
		path += i;
		i = 0;
	}
}

void	renew_pwd(char *path, t_bool is_changed)
{
	char	*str_pwd;
	char	**split;

	if (!is_current_dir_exist())
	{
		set_preserve_dir(path);
		if (is_changed)
			normalize_pwd(&g_request.pwd);
	}
	else
	{
		split = ft_split(path, '/');
		if (path[0] == '/')
			replace_pwd(split, TRUE);
		else
			replace_pwd(split, FALSE);
		normalize_pwd(&g_request.pwd);
		multi_free(split);
	}
	str_pwd = stringify_pwd(g_request.pwd);
	replace_env_value("PWD", str_pwd);
	free(str_pwd);
}
