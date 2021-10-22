/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsugiyam <tsugiyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 22:16:45 by tsugiyam          #+#    #+#             */
/*   Updated: 2021/10/22 22:00:23 by tsugiyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

void	prepare_token_types(char **token_types)
{
	token_types[TYPE_R_RDRCT] = ft_strdup(">");
	token_types[TYPE_RR_RDRCT] = ft_strdup(">>");
	token_types[TYPE_L_RDRCT] = ft_strdup("<");
	token_types[TYPE_LL_RDRCT] = ft_strdup("<<");
	token_types[TYPE_PIPE] = ft_strdup("|");
}

void	dispose_token_types(char **token_types)
{
	int	i;

	i = -1;
	while (++i < TOKEN_TYPE_NUM)
		free(token_types[i]);
}

t_token_type	get_token_type(char *token)
{
	char	*token_types[TOKEN_TYPE_NUM];
	int		token_type;

	prepare_token_types(token_types);
	token_type = -1;
	while (++token_type < TOKEN_TYPE_NUM)
		if (!ft_strcmp(token_types[token_type], token))
			break ;
	dispose_token_types(token_types);
	if (token_type == TYPE_STR)
		while (*token && token_type != TYPE_EXPDBL)
			if (is_quote(*token) || *token++ == DLL)
				token_type = TYPE_EXPDBL;
	return (token_type);
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

t_bool	is_delimiter(int c)
{
	return (ft_strchr_i(DELIMITERS, c) != -1);
}

t_bool	find_closing_qt(char *line, int *i)
{
	char	qt;

	qt = line[*i];
	while (line[++*i])
		if (line[*i] == qt)
			return (TRUE);
	return (FALSE);
}

t_bool	is_redirect(char c)
{
	return (c == R_RDRCT || c == L_RDRCT);
}

t_bool	is_doble_redirect(char *line)
{
	return (is_redirect(line[0]) && line[0] == line[1]);
}

void	get_delimiter(t_token **head, char **line)
{
	int	n;

	clear_white(line);
	if (!**line || !is_delimiter(**line))
		return ;
	n = 1;
	if (is_doble_redirect(*line))
		n++;
	append_token(head, new_token(ft_strndup(*line, n)));
	*line += n;
}

void	get_token(t_token **head, char **line)
{
	int	i;

	i = -1;
	clear_white(line);
	while ((*line)[++i] && !is_delimiter((*line)[i]))
		if (is_quote((*line)[i]))
			find_closing_qt(*line, &i);
	if (i != 0)
		append_token(head, new_token(ft_strndup(*line, i)));
	*line += i;
}

void	print_tokens(t_token *head)
{
	t_token	*token;

	token = head;
	while (token)
	{
		printf("token token:%s\n", token->token);
		printf("token type:%u\n", token->type);
		token = token->next;
	}
}

void	tokenize(t_token **head, char *line)
{
	while (*line)
	{
		get_token(head, &line);
		get_delimiter(head, &line);
	}
}
