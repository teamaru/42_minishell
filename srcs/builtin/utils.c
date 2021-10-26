/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsugiyam <tsugiyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 12:58:43 by tsugiyam          #+#    #+#             */
/*   Updated: 2021/10/26 12:17:22 by tsugiyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

extern t_request	g_request;

t_bool	is_key_exist(char *key)
{
	t_environ	*environ;

	environ = g_request.environs;
	while (environ)
	{
		if (!ft_strcmp(environ->key, key))
			return (TRUE);
		environ = environ->next;
	}
	return (FALSE);
}

t_bool	is_valid_identifier(const char *arg)
{
	int	i;

	if (!arg[0])
		return (FALSE);
	if (ft_isdigit(arg[0]))
		return (FALSE);
	i = -1;
	while (arg[++i])
		if (arg[i] == SPC)
			return (FALSE);
	return (TRUE);
}

t_exit_cd	return_or_exit(t_exit_cd exit_cd, t_bool is_child_process)
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
