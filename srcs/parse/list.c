/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsugiyam <tsugiyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 22:33:06 by tsugiyam          #+#    #+#             */
/*   Updated: 2021/10/22 22:33:06 by tsugiyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

void	free_cmd_list(t_cmd **head)
{
	t_cmd	*cmd;
	t_cmd	*next;

	if (!head)
		return ;
	cmd = *head;
	while (cmd)
	{
		next = cmd->next;
		free_tokens(&cmd->args);
		free_tokens(&cmd->rds);
		free(cmd);
		cmd = next;
		next = NULL;
	}
	*head = NULL;
}

t_cmd	*new_cmd(void)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->prev = NULL;
	new->next = NULL;
	new->args = NULL;
	new->rds = NULL;
	return (new);
}

void	append_cmd(t_cmd **head, t_cmd *new)
{
	t_cmd	*cmd;

	if (!head || !new)
		return ;
	if (!*head)
	{
		*head = new;
		return ;
	}
	cmd = *head;
	while (cmd && cmd->next)
		cmd = cmd->next;
	cmd->next = new;
	new->prev = cmd;
}
