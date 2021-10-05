/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnakahod <jnakahod@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 16:54:14 by jnakahod          #+#    #+#             */
/*   Updated: 2021/10/02 19:15:23 by jnakahod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

static int		counst_args(t_token *args)
{
	t_token *tmp;
	int		res;

	tmp = args;
	res = 0;
	while (tmp)
	{
		res++;
		tmp = tmp->next;
	}
	return (res);
}

const char	**create_cmd_args(t_token *args)
{
	const char	**res;
	int		i;
	int		ac;
	t_token	*arg;

	ac = counst_args(args);
	res = (const char **)malloc(sizeof(char *) * (ac + 1));
	if (!res)
		return (NULL);
	arg = args;
	i = 0;
	while(arg)
	{
		res[i] = ft_strdup(arg->token);
		arg = arg->next;
		i++;
	}
	res[i] = NULL;
	return (res);
}
