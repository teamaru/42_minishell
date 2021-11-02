/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnakahod <jnakahod@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 15:05:50 by jnakahod          #+#    #+#             */
/*   Updated: 2021/10/26 14:40:20 by jnakahod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

extern t_request	g_request;

void	update_shlvl(void)
{
	t_environ	*shlvl_node;
	int			new_lvl;
	char		*c_new_lvl;

	shlvl_node = get_target_environ("SHLVL");
	if (shlvl_node)
	{
		new_lvl = ft_atoi(shlvl_node->value) + 1;
		if (new_lvl > 999)
			replace_env_value("SHLVL", NULL);
		else
		{
			c_new_lvl = ft_itoa(new_lvl);
			replace_env_value("SHLVL", c_new_lvl);
			free(c_new_lvl);
		}
	}
	else
	{
		append_environ(&g_request.environs,
			new_environ(ft_strdup("SHLVL"), ft_strdup("1"), FALSE));
	}
}
