/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsugiyam <tsugiyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 15:07:13 by tsugiyam          #+#    #+#             */
/*   Updated: 2021/09/16 15:07:14 by tsugiyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

void free_cmd_list(t_cmd **head)
{
  t_cmd	*cmd;
	t_cmd	*next;

	if (!head)
		return ;
  cmd = *head;
	while (cmd)
	{
		next = cmd->next;
		free(cmd->cmd);
		free(cmd);
		cmd = next;
		next = NULL;
	}
	*head = NULL;
}

t_cmd	*new_cmd(char *cmd)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->cmd = ft_strdup(cmd);
  free(cmd);
	new->prev = NULL;
	new->next = NULL;
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

void print_cmds(t_request *request)
{
  t_cmd *cmd;
  cmd = request->cmds;
  while(cmd)
  {
    printf("cmd :%s\n", cmd->cmd);
    cmd = cmd->next;
  }
}

void parse(t_request *request)
{
  t_token *token = request->tokens;
  while (token)
  {
    append_cmd(&request->cmds, new_cmd(ft_strdup(token->token)));
    token = token->next;
  }
  print_cmds(request);
}

t_bool is_type_redirect(t_token *token)
{
  return (token->type == TYPE_R_RDRCT
      || token->type == TYPE_RR_RDRCT
      || token->type == TYPE_L_RDRCT
      || token->type == TYPE_LL_RDRCT);
}

t_bool is_type_meta(t_token *token)
{
  return (token->type == TYPE_PIPE);
}

t_bool is_quote_closed(t_token *token)
{
  int i;
  t_bool is_quote_closed;

  i = -1;
  is_quote_closed = TRUE;
  while (token->token[++i])
    if (is_quote(token->token[i]))
      is_quote_closed = find_closing_qt(token->token, &i);
  return (is_quote_closed);
}

t_bool is_valid_syntax(t_request *request)
{
  t_token *token;

  token = request->tokens;
  if (!token)
    return (TRUE);
  if (is_type_meta(token))
    return (FALSE);
  while (token)
  {
    if (!is_quote_closed(token))
      return (FALSE);
    if (!token->next)
      break ;
    if ((is_type_meta(token) && is_type_meta(token->next))
      || (is_type_redirect(token) && is_type_meta(token->next))
      || (is_type_redirect(token) && is_type_redirect(token->next)))
      return (FALSE);
    token = token->next;
  }
  if (is_type_redirect(token))
    return (FALSE);
  return (TRUE);
}
