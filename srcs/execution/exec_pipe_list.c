/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnakahod <jnakahod@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 21:29:47 by jnakahod          #+#    #+#             */
/*   Updated: 2021/10/02 23:08:58 by jnakahod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

static void	execute_cmd_in_child(t_pipe_list *pipe_list)
{
	const char	**cmd_args;

	//t_redirection_listがあれば参照先変更
	if (change_multi_references(pipe_list) < 0)
	{
		perror("in change_multi_references");
		exit(1);
	}
	cmd_args = pipe_list->cmd_args;
	if (execve(cmd_args[0], (char *const *)cmd_args, NULL) < 0)
	{
		perror("execve");
		exit(1);
	}
}

void	exec_pipe_list(t_pipe_list *pipe_list)
{
	pid_t	child_pid;
	pid_t	changed_pid;
	int		status;

	//一度だけforkして子プロセス作成
	child_pid = fork();
	if (child_pid == -1)
	{
		perror("fork");
		return ;
	}
	//子プロセスで実行
	if (child_pid == 0)
	{
		execute_cmd_in_child(pipe_list);
	}
	//親プロセスで実行
	else
	{
		changed_pid = waitpid(child_pid, &status, 0);
		if (changed_pid == -1)
		{
			perror("waitpid");
			return ;
		}
	}
}
