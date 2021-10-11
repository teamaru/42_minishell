/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsugiyam <tsugiyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 12:28:55 by tsugiyam          #+#    #+#             */
/*   Updated: 2021/09/23 12:28:55 by tsugiyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

extern t_request g_request;

t_bool is_env_end(char c)
{
  return (c == '\0' || c == DLL || c == SPC || c == SLSH || c == QSTN || is_quote(c));
}

char *get_env_key(char *token)
{
  int i;
  char *key;

  if (!*token)
    return (NULL);
  i = 0;
  key = NULL;
  while (!is_env_end(token[i]))
    i++;
  if (token[i] == QSTN)
    i++;
  if (i > 0)
    key = ft_strndup(token, i);
  return (key);
}

char *get_env_value(char *key)
{
  t_environ *environ;

  if (!key)
    return (NULL);
  if (*key == QSTN)
    return (ft_itoa(errno));
  environ = g_request.environs;
  while (environ)
  {
    if (!ft_strcmp(environ->key, key))
      return (ft_strdup(environ->value));
    environ = environ->next;
  }
  return (NULL);
}

void replace_token(t_token *token, char *new_token)
{
  free(token->token);
  token->token = new_token;
}

char *join_expanded_tokens(t_token *expanded_tokens)
{
  t_token *tmp_token;
  char *joined_token;
  char *tmp;

  tmp_token = expanded_tokens;
  joined_token = NULL;
  while (tmp_token)
  {
    tmp = joined_token;
    joined_token = ft_strjoin(joined_token, tmp_token->token);
    free(tmp);
    tmp_token = tmp_token->next;
  }
  return (joined_token);
}

int get_str_len(char *token)
{
  char qt;
  int len;

  if (!token || !is_quote(*token))
    return (0);
  len = 1;
  qt = *token;
  while (token[len] && token[len] != qt)
    len++;
  return (len - 1);
}

void expand_quote(char **token, t_token **expanded_tokens)
{
  int i;
  int len;

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

int get_env_len(char *token)
{
  int len;

  len = 0;
  while (!is_env_end(token[len]))
    len++;
  if (token[len] == QSTN)
    len++;
  return (len);
}

void expand_env(char **token, t_token **expanded_tokens)
{
  int i;
  char *key;
  char *value;

  i = -1;
  while ((*token)[++i] && (*token)[i] != DLL)
    if ((*token)[i] == SGL_QT)
      find_closing_qt(*token, &i);
  if (i > 0)
    append_token(expanded_tokens, new_token(ft_strndup(*token, i)));
  if ((*token)[i])
    i++;
  *token += i;
  key = get_env_key(*token);
  value = get_env_value(key);
  free(key);
  if (value)
    append_token(expanded_tokens, new_token(value));
  *token += get_env_len(*token);
}

char *expand_token(t_expand_func expand_func, char *token)
{
  char *expanded_token;
  t_token *expanded_tokens;

  if (!token)
    return (NULL);
  expanded_tokens = NULL;
  while (*token)
    expand_func(&token, &expanded_tokens);
  expanded_token = join_expanded_tokens(expanded_tokens);
  free_tokens(&expanded_tokens);
  return (expanded_token);
}

void insert_token(t_token **head, t_token *new_token, t_token *target_token)
{
  t_token *prev;

  if (!head)
    return (free_tokens(&new_token));
  if (!*head)
    return (append_token(head, new_token));
  if (!target_token)
    return (free_tokens(&new_token));
  prev = target_token->prev;
  target_token->prev = new_token;
  new_token->next = target_token;
  new_token->prev = prev;
  if (prev)
    prev->next = new_token;
  else
    *head = new_token;
}

void insert_tokens(t_token **head, t_token *new_tokens, t_token *target_token)
{
  t_token *new_token;
  t_token *next;

  new_token = new_tokens;
  while (new_token)
  {
    next = new_token->next;
    insert_token(head, new_token, target_token);
    new_token = next;
  }
}

void move_token_head(t_token **head, t_token *token)
{
  *head = token->next;
  if (token->next)
    token->next->prev = NULL;
  token->next = NULL;
  token->prev = NULL;
  free_tokens(&token);
}

void delete_token(t_token **head, t_token *target_token)
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

void get_word(t_token **new_tokens, char **line)
{
  int i;

  i = -1;
  clear_white(line);
  while ((*line)[++i] && !is_white((*line)[i]))
    if (is_quote((*line)[i]))
      find_closing_qt(*line, &i);
  if (i != 0)
    append_token(new_tokens, new_token(ft_strndup(*line, i)));
  *line += i;
}

void split_word(t_token **new_tokens, char *token)
{
  while (token && *token)
    get_word(new_tokens, &token);
}

t_bool is_file_path(t_token *token)
{
  t_token *prev;

  prev = token->prev;
  if (!prev)
    return (FALSE);
  return (is_type_redirect(prev));
}


t_bool is_eos_token(t_token *token)
{
  t_token *prev;

  prev = token->prev;
  if (!prev)
    return (FALSE);
  return (is_type_heredoc(prev));
}

t_bool split_token(t_token **head, t_token **token)
{
  t_token *new_tokens;
  t_token *prev;

  new_tokens = NULL;
  split_word(&new_tokens, (*token)->token);
  if (is_file_path(*token) && token_listsize(new_tokens) != 1)
    return (print_err_msg(ERR_MSG_AMBGS_RDRCT));
  insert_tokens(head, new_tokens, *token);
  prev = (*token)->prev;
  delete_token(head, *token);
  *token = prev;
  return (TRUE);
}

t_bool expand_tokens(t_token **head)
{
  t_token *token;

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

void test_token()
{
  t_token *token;

  token = g_request.cmds->args;
  while (token)
  {
    printf("forward :%s\n", token->token);
    token = token->next;
  }
  token = g_request.cmds->args;
  while (token && token->next)
    token = token->next;
  while (token)
  {
    printf("back :%s\n", token->token);
    token = token->prev;
  }
}

t_bool expand()
{
  t_cmd *cmd;

  cmd = g_request.cmds;
  while (cmd)
  {
    expand_tokens(&cmd->args);
    if (!expand_tokens(&cmd->rds))
      return (FALSE);
    cmd = cmd->next;
  }
  print_cmds(g_request.cmds);
  return (TRUE);
}


void replace_env_value(char *target_key, char *new_value)
{
  t_environ *target_environ;

  target_environ = get_target_environ(target_key);
  if (!target_environ)
    return ;
  free(target_environ->value);
  target_environ->value = ft_strdup(new_value);
}

t_environ *get_target_environ(const char *key)
{
  t_environ *environ;

  environ = g_request.environs;
  while (environ)
  {
    if (!ft_strcmp(environ->key, key))
      return (environ);
    environ = environ->next;
  }
  return (NULL);
}


void free_environs(t_environ **head)
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

void move_environ_head(t_environ **head, t_environ *environ)
{
  *head = environ->next;
  if (environ->next)
    environ->next->prev = NULL;
  environ->next = NULL;
  environ->prev = NULL;
  free_environs(&environ);
}

void delete_environ(t_environ **head, t_environ *target_environ)
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

void print_environ(t_environ *head)
{
  t_environ *environ;

  environ = head;
  while (environ)
  {
    printf("environ key :%s\n", environ->key);
    printf("environ value :%s\n", environ->value);
    environ = environ->next;
  }
}

void make_environ_hash(void)
{
  extern char **environ;
  char **env;
  char **split;

  env = environ;
  g_request.environs = NULL;
  while (*env)
  {
    split = ft_split(*env++, '=');
    append_environ(&g_request.environs, new_environ(ft_strdup(split[0]), ft_strdup(split[1])));
    multi_free(split);
  }
}
