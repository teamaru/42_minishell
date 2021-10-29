/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnakahod <jnakahod@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 21:29:47 by jnakahod          #+#    #+#             */
/*   Updated: 2021/10/29 12:34:55 by jnakahod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

extern t_request	g_request;

t_exit_cd	is_correct_path(const char *cmd_path)
{
	char		*dir_path;
	int			dir_path_size;
	int			i;
	struct stat	buf;
	t_exit_cd	exit_cd;

	/*最後のスラッシュまでを文字列に*/
	exit_cd = SCCSS;
	i = -1;
	dir_path_size = 0;
	while (cmd_path[++i])
	{
		if (cmd_path[i] == '/')
			dir_path_size = i;
	}
	if (dir_path_size == 0)
		return  (exit_cd);
	dir_path = (char *)ft_calloc((dir_path_size + 1), sizeof(char));
	if (!dir_path)
		return (GNRL_ERR);
	ft_strlcpy(dir_path, cmd_path, dir_path_size + 1);
	// printf("dir_path = %s\n", dir_path);
	stat(dir_path, &buf);
	if (S_ISREG(buf.st_mode))
		exit_cd = DENIED;
	else if (!S_ISDIR(buf.st_mode))
		exit_cd = CMD_NOT_FND;
	// printf("dir_path correct!!\n");
	free(dir_path);
	return (exit_cd);
}

void	exec_path_cmd(t_pipe_list *pipe_list)
{
	const char	**cmd_args;
	char		**environs;
	t_exit_cd	enable_path;

	environs = env_list_to_array(g_request.environs);
	cmd_args = pipe_list->cmd_args;
	if (get_target_environ("PATH") && is_path_part((char *)cmd_args[0]))
		search_path((char **)cmd_args);
			// print_err_and_exit(NULL, DENIED);
	/*pathで指定されたdirが存在するかどうか*/
	enable_path = is_correct_path(cmd_args[0]);
	if (enable_path == DENIED)
		print_err_and_exit("Not a directory", DENIED);
	else if (enable_path == CMD_NOT_FND)
		print_err_and_exit(NULL, CMD_NOT_FND);
	// printf("cmd = %s\n", cmd_args[0]);
	if (access(cmd_args[0], F_OK) == -1)
		print_err_and_exit(NULL, CMD_NOT_FND);
	// printf("cmd = %s\n", cmd_args[0]);
	if (access(cmd_args[0], X_OK) == -1)
		print_err_and_exit(NULL, DENIED);
	if (execve(cmd_args[0], (char *const *)cmd_args, environs) < 0)
		print_err_and_exit(NULL, GNRL_ERR);
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
