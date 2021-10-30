/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnakahod <jnakahod@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 21:29:47 by jnakahod          #+#    #+#             */
/*   Updated: 2021/10/29 13:49:58by jnakahod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

extern t_request	g_request;

char	*get_dir_path(const char *cmd_path)
{
	char		*dir_path;
	int			dir_path_size;
	size_t		i;

	i = 0;
	dir_path_size = 0;
	while (cmd_path[i])
	{
		if (cmd_path[i] == '/')
			dir_path_size = i;
		i += 1;
	}
	dir_path = (char *)ft_calloc((dir_path_size + 1), sizeof(char));
	if (!dir_path)
		return (NULL);
	ft_strlcpy(dir_path, cmd_path, dir_path_size + 1);
	return (dir_path);
}

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
	if (exit_cd == DENIED)
		free_set((void **)err_msg, (void *)ft_strdup(ERR_MSG_NOT_DIR));
	else if (exit_cd == CMD_NOT_FND)
		free_set((void **)err_msg, (void *)ft_strdup(ERR_MSG_NO_FILE));
	return (exit_cd);
}

void	print_err_and_exit_free(char **msg, t_exit_cd exit_cd)
{
	print_err_msg(*msg, exit_cd);
	free_set((void **)msg, NULL);
	exit(exit_cd);
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
	if (exit_cd == DENIED)
		free_set((void **)err_msg, (void *)ft_strdup(ERR_MSG_IS_DIR));
	else if (exit_cd == CMD_NOT_FND)
		free_set((void **)err_msg, (void *)ft_strdup(ERR_MSG_INVLD_CMD));
	return (exit_cd);
}

t_exit_cd	can_execute_path_cmd(const char *cmd_path, char **err_msg)
{
	t_exit_cd	exit_cd;

	exit_cd = SCCSS;
	if (access(cmd_path, X_OK) == -1)
		exit_cd = DENIED;
	if (exit_cd == DENIED)
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

t_bool	is_enable_environ_path(void)
{
	t_environ *path;

	path = get_target_environ("PATH");
	if (!path || path->value[0] == '\0')
		return (FALSE);
	return (TRUE);
}

void	exec_path_cmd(t_pipe_list *pipe_list)
{
	const char	**cmd_args;
	char		**environs;
	t_exit_cd	exit_cd;
	struct stat	buf;
	char		*err_msg;

	environs = env_list_to_array(g_request.environs);
	cmd_args = pipe_list->cmd_args;
	err_msg = NULL;
	exit_cd = SCCSS;
	if (!is_path_part((char *)cmd_args[0]))
	{
		exit_cd = check_executable_cmd_path(cmd_args[0], &err_msg);
		if (exit_cd != SCCSS)
			print_err_and_exit_free(&err_msg, exit_cd);
		free(err_msg);
		if (execve(cmd_args[0], (char *const *)cmd_args, environs) < 0)
		{
			//rがある なら exit_cd 0
			stat(cmd_args[0], &buf);
			if (!access(cmd_args[0], R_OK))
				exit(0);
			//sizeがzeroならpermsisson
			else if (!buf.st_size)
			{
				print_err_and_exit(ERR_MSG_PERM_DENIED, DENIED);
			}
			else
				print_err_and_exit(NULL, GNRL_ERR);
		}
	}
	else
	{
		if (is_enable_environ_path() == FALSE)
			print_err_and_exit(ERR_MSG_NO_FILE, CMD_NOT_FND);

		search_path((char **)cmd_args);
		// printf("cmd = %s\n", cmd_args[0]);

		exit_cd = check_executable_cmd_path(cmd_args[0], &err_msg);
		if (exit_cd != SCCSS)
			print_err_and_exit_free(&err_msg, exit_cd);
		free(err_msg);
		if (execve(cmd_args[0], (char *const *)cmd_args, environs) < 0)
		{
			//rがある なら exit_cd 0
			stat(cmd_args[0], &buf);
			if (!access(cmd_args[0], R_OK))
				exit(0);
			//sizeがzeroならpermsisson
			else if (!buf.st_size)
			{
				print_err_and_exit(ERR_MSG_PERM_DENIED, DENIED);
			}
			else
				print_err_and_exit(NULL, GNRL_ERR);
		}
	}
	/*pathで指定されたdirが存在するかどうか*/
}

void	child_exec_cmd(t_pipe_list *pipe_list)
{
	t_builtin_id	builtin_id;

	if (change_multi_references(pipe_list) < 0)
		print_err_and_exit(NULL, GNRL_ERR);
	if (!pipe_list->cmd_args)
		exit(0);
	builtin_id = get_builtin_id(pipe_list->cmd_args[0]);
	if (builtin_id != NON_BUILTIN)
		g_request.builtin_funcs[builtin_id](pipe_list->cmd_args, TRUE);
	else
		exec_path_cmd(pipe_list);
}

void	wait_processes(t_pipe_list *pipe_list)
{
	pid_t		changed_pid;
	t_pipe_list	*tmp_node;
	int			status;

	tmp_node = pipe_list;
	while (tmp_node)
	{
		changed_pid = waitpid(tmp_node->pid, &status, 0);
		g_request.exit_cd = WEXITSTATUS(status);
		if (changed_pid < 0)
		{
			perror("waitpid");
			return ;
		}
		tmp_node = tmp_node->next;
	}
}

void	execute_cmds(t_pipe_list *pipe_list)
{
	t_builtin_id	builtin_id;

	if (pipe_list->cmd_args)
		builtin_id = get_builtin_id(pipe_list->cmd_args[0]);
	else
		builtin_id = NON_BUILTIN;
	if (!has_pipe(pipe_list) && builtin_id != NON_BUILTIN)
		exec_simple_buitin(pipe_list, builtin_id);
	else if (!has_pipe(pipe_list) && builtin_id == NON_BUILTIN)
		exec_simple_cmd(pipe_list);
	else
	{
		handle_pipelines(pipe_list);
		wait_processes(pipe_list);
	}
}
