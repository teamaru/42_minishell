/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsugiyam <tsugiyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 23:12:29 by tsugiyam          #+#    #+#             */
/*   Updated: 2021/11/02 21:37:34 by tsugiyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

extern t_request	g_request;

void	print_pwd(void)
{
	t_pwd	*pwd;

	pwd = g_request.pwd;
	ft_putstr_fd("/", STDOUT);
	while (pwd)
	{
		ft_putstr_fd(pwd->dir, STDOUT);
		pwd = pwd->next;
		if (pwd)
			ft_putstr_fd("/", STDOUT);
	}
	ft_putstr_fd("\n", STDOUT);
}

void	init_pwd(void)
{
	char	pwd[BUFSIZ];
	char	**split;
	int		i;

	getcwd(pwd, BUFSIZ);
	split = ft_split(pwd, '/');
	g_request.oldpwd = NULL;
	i = -1;
	while (split[++i])
		append_pwd(&g_request.pwd, new_pwd(ft_strdup(split[i])));
	multi_free(split);
}

t_exit_cd	execute_pwd(const char **cmd_args, t_bool is_child_process)
{
	(void)cmd_args;
	print_pwd();
	return (return_or_exit(SCCSS, is_child_process));
}
