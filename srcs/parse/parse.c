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

#include <mini_shell.h>

extern t_request g_request;

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
    free_tokens(&cmd->args);
    free_tokens(&cmd->rds);
		free(cmd);
		cmd = next;
		next = NULL;
	}
	*head = NULL;
}

t_cmd	*new_cmd()
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

void print_cmds(t_cmd *head)
{
  t_cmd *cmd;

  cmd = head;
  while(cmd)
  {
    t_token *args;
    t_token *rds;
    args = cmd->args;
    rds = cmd->rds;
    printf("-----------\n");
    while (args) {
      printf("cmd args\t:%s\n", args->token);
      args = args->next;
    }
    while (rds) {
      printf("cmd rds\t\t:%s\n", rds->token);
      rds = rds->next;
    }
    cmd = cmd->next;
  }
}

void parse()
{
  t_token *token;
  t_cmd *cmd;

  token = g_request.tokens;
  while (token)
  {
    cmd = new_cmd();
    while (token && token->type != TYPE_PIPE)
    {
      if (token->type == TYPE_STR || token->type == TYPE_EXPDBL)
        append_token(&cmd->args, new_token(ft_strdup(token->token)));
      else
      {
        append_token(&cmd->rds, new_token(ft_strdup(token->token)));
        token = token->next;
        append_token(&cmd->rds, new_token(ft_strdup(token->token)));
      }
      token = token->next;
    }
    append_cmd(&g_request.cmds, cmd);
    if (token)
      token = token->next;
  }
}


t_bool is_type_heredoc(t_token *token)
{
  return (token->type == TYPE_LL_RDRCT);
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

t_bool is_valid_token_pair(t_token *token)
{
  return (!((is_type_meta(token) && is_type_meta(token->next))
      || (is_type_redirect(token) && is_type_meta(token->next))
      || (is_type_redirect(token) && is_type_redirect(token->next))));
}

t_bool is_valid_syntax()
{
  t_token *token;

  token = g_request.tokens;
  if (!token)
    return (TRUE);
  if (is_type_meta(token))
    return (print_err_msg(ERR_MSG_INVLD_SYNTX, INVLD_SYNTX));
  while (token)
  {
    if (!is_quote_closed(token))
      return (print_err_msg(ERR_MSG_QT_NOT_CLSD, GNRL_ERR));
    if (!token->next)
      break ;
    if (!is_valid_token_pair(token))
      return (print_err_msg(ERR_MSG_INVLD_SYNTX, GNRL_ERR));
    token = token->next;
  }
  if (is_type_redirect(token) || is_type_meta(token))
    return (print_err_msg(ERR_MSG_INVLD_SYNTX, INVLD_SYNTX));
  return (TRUE);
}
