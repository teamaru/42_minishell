/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_executable_cmd_path.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnakahod <jnakahod@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 16:19:39 by jnakahod          #+#    #+#             */
/*   Updated: 2021/10/30 16:58:08 by jnakahod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

t_exit_cd	is_correct_dir_path(const char *cmd_path, char **err_msg)
{
	char		*dir_path;
	struct stat	buf;
	t_exit_cd	exit_cd;

	exit_cd = SCCSS;
	dir_path = get_dir_path(cmd_path);
	if (!dir_path)
		return (GNRL_ERR);
	else if (dir_path[0] != '\0')
	{
		stat(dir_path, &buf);
		if (S_ISREG(buf.st_mode))
			exit_cd = DENIED;
		else if (!S_ISDIR(buf.st_mode))
			exit_cd = CMD_NOT_FND;
	}
	free(dir_path);
	if (exit_cd == DENIED && err_msg)
		free_set((void **)err_msg, (void *)ft_strdup(ERR_MSG_NOT_DIR));
	else if (exit_cd == CMD_NOT_FND && err_msg)
		free_set((void **)err_msg, (void *)ft_strdup(ERR_MSG_NO_FILE));
	return (exit_cd);
}

t_exit_cd	is_correct_complete_path(const char *cmd_path, char **err_msg)
{
	t_exit_cd	exit_cd;
	struct stat	buf;

	exit_cd = SCCSS;
	stat(cmd_path, &buf);
	if (S_ISDIR(buf.st_mode))
		exit_cd = DENIED;
	else if (access(cmd_path, F_OK) == -1)
		exit_cd = CMD_NOT_FND;
	if (exit_cd == DENIED && err_msg)
		free_set((void **)err_msg, (void *)ft_strdup(ERR_MSG_IS_DIR));
	else if (exit_cd == CMD_NOT_FND && err_msg)
		free_set((void **)err_msg, (void *)ft_strdup(ERR_MSG_INVLD_CMD));
	return (exit_cd);
}

t_exit_cd	can_execute_path_cmd(const char *cmd_path, char **err_msg)
{
	t_exit_cd	exit_cd;

	exit_cd = SCCSS;
	if (access(cmd_path, X_OK) == -1)
		exit_cd = DENIED;
	if (exit_cd == DENIED && err_msg)
		free_set((void **)err_msg, (void *)ft_strdup(ERR_MSG_PERM_DENIED));
	return (exit_cd);
}

t_exit_cd	check_executable_cmd_path(const char *cmd_path, char **err_msg)
{
	t_exit_cd	exit_cd;

	exit_cd = SCCSS;
	if (exit_cd == SCCSS)
		exit_cd = is_correct_dir_path(cmd_path, err_msg);
	if (exit_cd == SCCSS)
		exit_cd = is_correct_complete_path(cmd_path, err_msg);
	if (exit_cd == SCCSS)
		exit_cd = can_execute_path_cmd(cmd_path, err_msg);
	return (exit_cd);
}
