/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsugiyam <tsugiyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 22:39:50 by tsugiyam          #+#    #+#             */
/*   Updated: 2021/10/22 22:39:50 by tsugiyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

void	insert_tokens(t_token **head,
	t_token *new_tokens, t_token *target_token)
{
	t_token	*new_token;
	t_token	*next;

	new_token = new_tokens;
	while (new_token)
	{
		next = new_token->next;
		insert_token(head, new_token, target_token);
		new_token = next;
	}
}

void	replace_token(t_token *token, char *new_token)
{
	free(token->token);
	token->token = new_token;
}

int	token_listsize(t_token *tokens)
{
	int		size;
	t_token	*token;

	token = tokens;
	size = 0;
	while (token)
	{
		size++;
		token = token->next;
	}
	return (size);
}

char	**token_list_to_array(t_token *tokens)
{
	int		i;
	char	**array;
	t_token	*token;

	array = malloc(sizeof(char *) * (token_listsize(tokens) + 1));
	if (!array)
		return (NULL);
	token = tokens;
	i = -1;
	while (token)
	{
		array[++i] = ft_strdup(token->token);
		token = token->next;
	}
	array[i + 1] = NULL;
	return (array);
}
