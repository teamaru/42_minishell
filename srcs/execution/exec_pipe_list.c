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

t_bool	is_enable_environ_path(void)
{
	t_environ *path;

	path = get_target_environ("PATH");
	if (!path || path->value[0] == '\0')
		return (FALSE);
	return (TRUE);
}

static void replace_path(char **cmd, char *path)
{
	free(cmd[0]);
	cmd[0] = ft_strdup(path);
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
			stat(cmd_args[0], &buf);
			if (!access(cmd_args[0], R_OK))
				exit(0);
			else if (!buf.st_size)
				print_err_and_exit(ERR_MSG_PERM_DENIED, DENIED);
			else
				print_err_and_exit(NULL, GNRL_ERR);
		}
	}
	else
	{
		if (is_enable_environ_path() == FALSE)
			print_err_and_exit(ERR_MSG_NO_FILE, CMD_NOT_FND);

		t_environ *path;
		char **paths;
		int i;
		t_bool	flag;

		path = get_target_environ("PATH");
		paths = split_path(path->value, ':');
		i = -1;
		flag = FALSE;
		while (paths[++i])
		{
			exit_cd = SCCSS;
			paths[i] = add_slash(paths[i]);
			paths[i] = join_path(paths[i], (char *)cmd_args[0]);
			exit_cd = check_executable_cmd_path(paths[i], NULL);
			if (!flag && exit_cd == DENIED)
				flag = TRUE;
			if (exit_cd != SCCSS)
				continue;
			replace_path((char **)cmd_args, paths[i]);
			break;
		}
		multi_free(paths);
		if (exit_cd != SCCSS && flag)
			exit_cd = DENIED;
		if (exit_cd == DENIED)
			print_err_and_exit(ERR_MSG_PERM_DENIED, DENIED);
		else if (exit_cd != SCCSS)
			print_err_and_exit(ERR_MSG_NO_FILE, CMD_NOT_FND);

		if (execve(cmd_args[0], (char *const *)cmd_args, environs) < 0)
		{
			stat(cmd_args[0], &buf);
			if (!access(cmd_args[0], R_OK))
				exit(0);
			else if (!buf.st_size)
				print_err_and_exit(ERR_MSG_PERM_DENIED, DENIED);
			else
				print_err_and_exit(NULL, GNRL_ERR);
		}
	}
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
