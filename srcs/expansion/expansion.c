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

char *get_environment_key(char *token)
{
  int i;
  char *key;

  i = 0;
  key = NULL;
  while (token[i] && token[i] != SPC)
    i++;
  if (i > 1)
    key = ft_strndup(token + 1, i - 1);
  return (key);
}

char *get_environ_value(t_request *request, char *key)
{
  t_environ *environ;

  if (!key)
    return (NULL);
  environ = request->environs;
  while (environ)
  {
    if (!ft_strcmp(environ->key, key))
      return (environ->value);
    environ = environ->next;
  }
  return (NULL);
}

void replace_token(t_token *token, char *new_token)
{
  free(token->token);
  token->token = new_token;
}

char *join_tmp_tokens(t_token *tmp_tokens)
{
  t_token *tmp_token;
  char *joined_token;
  char *tmp;

  tmp_token = tmp_tokens;
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

  len = 0;
  qt = *token;
  while (token[len] && token[len] != qt)
    len++;
  return (len);
}

void get_tmp_token(char **token, t_token **tmp_tokens)
{
  int i;
  int len;

  i = 0;
  while ((*token)[i] && !is_quote((*token)[i]))
    i++;
  if (i > 0)
    append_token(tmp_tokens, new_token(ft_strndup(*token, i)));
  *token += i;
  len = get_str_len(*token);
  if (len > 0)
    append_token(tmp_tokens, new_token(ft_substr(*token, 0, len)));
  if ((*token)[len])
    len++;
  *token += len;
}

char *eliminate_quote(char *token)
{
  t_token *tmp_tokens;
  char *new_token;

  tmp_tokens = NULL;
  while (*token)
    get_tmp_token(&token, &tmp_tokens);
  new_token = join_tmp_tokens(tmp_tokens);
  free_tokens(&tmp_tokens);
  return (new_token);
}

void expand_tokens(t_token *head)
{
  t_token *token;

  token = head;
  while (token)
  {
    if (token->type == TYPE_EXPDBL)
      replace_token(token, eliminate_quote(token->token));
    token = token->next;
  }
}

void expand_environment_variable(t_request *request, char *s)
{
  char *key;
  char *value;

  key = get_environment_key(s);
  printf("key :%s\n", key);
  value = get_environ_value(request, key);
  printf("environ :%s\n", value);
}

void expand(t_request *request)
{
  t_cmd *cmd;

  cmd = request->cmds;
  while (cmd)
  {
    expand_tokens(cmd->args);
    expand_tokens(cmd->rds);
    cmd = cmd->next;
  }
  expand_environment_variable(request, "$USER tt est sts e");
  print_cmds(request->cmds);
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

void make_environ_hash(t_request *request)
{
  extern char **environ;
  char **env;
  char **split;

  env = environ;
  request->environs = NULL;
  while (*env)
  {
    split = ft_split(*env++, '=');
    append_environ(&request->environs, new_environ(ft_strdup(split[0]), ft_strdup(split[1])));
    multi_free(split);
  }
}
