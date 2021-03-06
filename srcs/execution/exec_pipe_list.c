/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnakahod <jnakahod@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 21:29:47 by jnakahod          #+#    #+#             */
/*   Updated: 2021/11/13 17:18:19 by jnakahod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

extern t_request	g_request;

void	call_execve_function(const char **cmd_args)
{
	char		**environs;
	struct stat	buf;

	environs = env_list_to_array(g_request.environs);
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

void	exec_path_cmd(t_pipe_list *pipe_list)
{
	const char	**cmd_args;
	t_exit_cd	exit_cd;
	char		*err_msg;

	cmd_args = pipe_list->cmd_args;
	err_msg = NULL;
	exit_cd = SCCSS;
	if (!is_path_part((char *)cmd_args[0]) || is_enable_environ_path() == FALSE)
	{
		if (is_path_part((char *)cmd_args[0]) && !is_enable_environ_path())
			free_set((void **)&cmd_args[0], ft_strjoin("./", cmd_args[0]));
		exit_cd = check_executable_cmd_path(cmd_args[0], &err_msg);
		if (exit_cd != SCCSS)
			print_err_and_exit_free(&err_msg, exit_cd);
		free(err_msg);
	}
	else
	{
		exit_cd = search_path((char **)cmd_args);
		if (exit_cd == DENIED)
			print_err_and_exit(ERR_MSG_PERM_DENIED, DENIED);
		else if (exit_cd != SCCSS)
			print_err_and_exit(ERR_MSG_INVLD_CMD, CMD_NOT_FND);
	}
	call_execve_function(cmd_args);
}

void	child_exec_cmd(t_pipe_list *pipe_list)
{
	t_builtin_id	builtin_id;
	char			*err_msg;

	err_msg = NULL;
	quit_act_in_execution();
	if (change_multi_references(pipe_list, &err_msg) < 0)
		print_err_and_exit_free(&err_msg, GNRL_ERR);
	if (!pipe_list->cmd_args)
		exit(0);
	builtin_id = get_builtin_id(pipe_list->cmd_args[0]);
	if (builtin_id != NON_BUILTIN)
		g_request.builtin_funcs[builtin_id](pipe_list->cmd_args, TRUE);
	else
		exec_path_cmd(pipe_list);
}

void	execute_cmds(t_pipe_list *pipe_list)
{
	t_builtin_id	builtin_id;
	pid_t			last_child_pid;

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
		last_child_pid = handle_pipelines(pipe_list);
		wait_processes(pipe_list, last_child_pid);
	}
	g_request.pid = 0;
	init_signal();
}
