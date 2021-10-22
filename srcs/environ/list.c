/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsugiyam <tsugiyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 22:22:59 by tsugiyam          #+#    #+#             */
/*   Updated: 2021/10/22 22:22:59 by tsugiyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

void	move_environ_head(t_environ **head, t_environ *environ)
{
	*head = environ->next;
	if (environ->next)
		environ->next->prev = NULL;
	environ->next = NULL;
	environ->prev = NULL;
	free_environs(&environ);
}

void	delete_environ(t_environ **head, t_environ *target_environ)
{
	if (!head || !*head || !target_environ)
		return ;
	if (*head == target_environ)
		return (move_environ_head(head, target_environ));
	target_environ->prev->next = target_environ->next;
	if (target_environ->next)
		target_environ->next->prev = target_environ->prev;
	target_environ->next = NULL;
	free_environs(&target_environ);
}

void	free_environs(t_environ **head)
{
	t_environ	*environ;
	t_environ	*next;

	if (!head)
		return ;
	environ = *head;
	while (environ)
	{
		next = environ->next;
		free(environ->key);
		free(environ->value);
		free(environ);
		environ = next;
		next = NULL;
	}
	*head = NULL;
}

t_environ	*new_environ(char *key, char *value)
{
	t_environ	*new;

	new = malloc(sizeof(t_environ));
	if (!new)
		return (NULL);
	new->key = key;
	new->value = value;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

void	append_environ(t_environ **head, t_environ *new)
{
	t_environ	*environ;

	if (!head || !new)
		return ;
	if (!*head)
	{
		*head = new;
		return ;
	}
	environ = *head;
	while (environ && environ->next)
		environ = environ->next;
	environ->next = new;
	new->prev = environ;
}
