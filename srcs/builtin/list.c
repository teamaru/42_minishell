/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsugiyam <tsugiyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 22:11:40 by tsugiyam          #+#    #+#             */
/*   Updated: 2021/10/31 22:11:40 by tsugiyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

extern t_request	g_request;

void	move_pwd_head(t_pwd **head, t_pwd *pwd)
{
	*head = pwd->next;
	if (pwd->next)
		pwd->next->prev = NULL;
	pwd->next = NULL;
	pwd->prev = NULL;
	free_pwd(&pwd);
}

void	delete_pwd(t_pwd **head, t_pwd *target_pwd)
{
	if (!head || !*head || !target_pwd)
		return ;
	if (*head == target_pwd)
		return (move_pwd_head(head, target_pwd));
	target_pwd->prev->next = target_pwd->next;
	if (target_pwd->next)
		target_pwd->next->prev = target_pwd->prev;
	target_pwd->next = NULL;
	free_pwd(&target_pwd);
}

void	free_pwd(t_pwd **head)
{
	t_pwd	*pwd;
	t_pwd	*next;

	if (!head)
		return ;
	pwd = *head;
	while (pwd)
	{
		next = pwd->next;
		free(pwd->dir);
		free(pwd);
		pwd = next;
		next = NULL;
	}
	*head = NULL;
}

t_pwd	*new_pwd(char *dir)
{
	t_pwd	*new;

	new = malloc(sizeof(t_pwd));
	if (!new)
		return (NULL);
	new->dir = dir;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

void	append_pwd(t_pwd **head, t_pwd *new)
{
	t_pwd	*pwd;

	if (!head || !new)
		return ;
	if (!*head)
	{
		*head = new;
		return ;
	}
	pwd = *head;
	while (pwd && pwd->next)
		pwd = pwd->next;
	pwd->next = new;
	new->prev = pwd;
}
