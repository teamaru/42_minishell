/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnakahod <jnakahod@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 12:28:55 by tsugiyam          #+#    #+#             */
/*   Updated: 2021/10/30 17:23:53 by jnakahod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

extern t_request	g_request;

t_bool	expand_tokens(t_token **head)
{
	t_token	*token;

	token = *head;
	while (token)
	{
		if (token->type == TYPE_EXPDBL)
		{
			if (!is_eos_token(token))
				replace_token(token, expand_token(expand_env, token->token));
			if (!split_token(head, &token))
				return (FALSE);
			if (!token)
				continue ;
			if (!is_eos_token(token))
				replace_token(token, expand_token(expand_quote, token->token));
		}
		token = token->next;
	}
	return (TRUE);
}

void	expand_quote(char **token, t_token **expanded_tokens)
{
	int	i;
	int	len;

	i = 0;
	while ((*token)[i] && !is_quote((*token)[i]))
		i++;
	if (i > 0)
		append_token(expanded_tokens, new_token(ft_strndup(*token, i)));
	*token += i;
	len = get_str_len(*token);
	if (len > 0)
		append_token(expanded_tokens, new_token(ft_substr(*token, 1, len)));
	if ((*token)[len])
		len++;
	*token += len;
}

int	keylen(char *s)
{
	int	len;

	len = 0;
	while (s && s[len] && !is_env_end(s[len]))
		len++;
	return (len);
}

void	move_token_pointer(char **token, int i)
{
	if ((*token)[i])
		i++;
	*token += i;
}

void	expand_env(char **token, t_token **expanded_tokens)
{
	int		i;
	char	*key;
	char	*value;

	i = -1;
	while ((*token)[++i] && (*token)[i] != DLL)
		if ((*token)[i] == SGL_QT)
			find_closing_qt(*token, &i);
	if (i > 0)
		append_token(expanded_tokens, new_token(ft_strndup(*token, i)));
	if ((*token)[i])
		i++;
	key = get_env_key(*token + i);
	if ((*token)[i - 1] == DLL && !key)
	{
		append_token(expanded_tokens, new_token(ft_strndup((*token + i - 1), 1)));
		*token += i;
		return ;
	}
	*token += i;
	value = get_env_value(key);
	free(key);
	if (value)
		append_token(expanded_tokens, new_token(value));
	*token += get_env_len(*token);
}

char	*expand_token(t_expand_func expand_func, char *token)
{
	char	*expanded_token;
	t_token	*expanded_tokens;

	if (!token)
		return (NULL);
	expanded_tokens = NULL;
	while (*token)
		expand_func(&token, &expanded_tokens);
	expanded_token = join_expanded_tokens(expanded_tokens);
	free_tokens(&expanded_tokens);
	return (expanded_token);
}

t_bool	expand(void)
{
	t_cmd	*cmd;

	cmd = g_request.cmds;
	while (cmd)
	{
		expand_tokens(&cmd->args);
		if (!expand_tokens(&cmd->rds))
			return (FALSE);
		cmd = cmd->next;
	}
	return (TRUE);
}
