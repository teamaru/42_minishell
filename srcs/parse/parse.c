/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsugiyam <tsugiyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 15:07:13 by tsugiyam          #+#    #+#             */
/*   Updated: 2021/10/22 22:04:01 by tsugiyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

extern t_request	g_request;

void	print_cmds(t_cmd *head)
{
	t_cmd	*cmd;
	t_token	*args;
	t_token	*rds;

	cmd = head;
	while (cmd)
	{
		args = cmd->args;
		rds = cmd->rds;
		printf("-----------\n");
		while (args)
		{
			printf("cmd args\t:%s\n", args->token);
			args = args->next;
		}
		while (rds)
		{
			printf("cmd rds\t\t:%s\n", rds->token);
			rds = rds->next;
		}
		cmd = cmd->next;
	}
}

t_bool	is_valid_syntax(void)
{
	t_token	*token;

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
			return (print_err_msg(ERR_MSG_INVLD_SYNTX, INVLD_SYNTX));
		token = token->next;
	}
	if (is_type_redirect(token) || is_type_meta(token))
		return (print_err_msg(ERR_MSG_INVLD_SYNTX, INVLD_SYNTX));
	return (TRUE);
}

void	parse(void)
{
	t_token	*token;
	t_cmd	*cmd;

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
