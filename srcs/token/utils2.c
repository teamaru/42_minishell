/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsugiyam <tsugiyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 22:41:18 by tsugiyam          #+#    #+#             */
/*   Updated: 2021/10/22 22:41:18 by tsugiyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

extern t_request	g_request;

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

t_bool	find_closing_qt(char *line, int *i)
{
	char	qt;

	qt = line[*i];
	while (line[++*i])
		if (line[*i] == qt)
			return (TRUE);
	return (FALSE);
}

void	test_token(void)
{
	t_token	*token;

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
