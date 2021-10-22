/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsugiyam <tsugiyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 22:35:02 by tsugiyam          #+#    #+#             */
/*   Updated: 2021/10/22 22:35:02 by tsugiyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

void	move_token_head(t_token **head, t_token *token)
{
	*head = token->next;
	if (token->next)
		token->next->prev = NULL;
	token->next = NULL;
	token->prev = NULL;
	free_tokens(&token);
}

void	delete_token(t_token **head, t_token *target_token)
{
	if (!head || !*head || !target_token)
		return ;
	if (*head == target_token)
		return (move_token_head(head, target_token));
	target_token->prev->next = target_token->next;
	if (target_token->next)
		target_token->next->prev = target_token->prev;
	target_token->next = NULL;
	free_tokens(&target_token);
}

void	free_tokens(t_token **head)
{
	t_token	*token;
	t_token	*next;

	if (!head)
		return ;
	token = *head;
	while (token)
	{
		next = token->next;
		free(token->token);
		free(token);
		token = next;
		next = NULL;
	}
	*head = NULL;
}

t_token	*new_token(char *token)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->token = token;
	new->type = get_token_type(new->token);
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

void	append_token(t_token **head, t_token *new)
{
	t_token	*token;

	if (!head || !new)
		return ;
	if (!*head)
	{
		*head = new;
		return ;
	}
	token = *head;
	while (token && token->next)
		token = token->next;
	token->next = new;
	new->prev = token;
}
