/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnakahod <jnakahod@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 12:33:54 by jnakahod          #+#    #+#             */
/*   Updated: 2021/10/21 16:30:19 by jnakahod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

extern t_request	g_request;

static char	*update_heredoc(char **old, char *input)
{
	char	*joined_input;
	char	*new_heredoc;

	joined_input = NULL;
	new_heredoc = NULL;
	joined_input = ft_strjoin(*old, input);
	free_set((void **)old, NULL);
	if (!joined_input)
		return (NULL);
	new_heredoc = ft_strjoin(joined_input, "\n");
	free_set((void **)&joined_input, NULL);
	if (!new_heredoc)
		return (NULL);
	return (new_heredoc);
}

static t_bool	can_exit_heredocument(char *input, char *delimiter)
{
	if (!input || is_match_str(input, delimiter))
		return (TRUE);
	else
		return (FALSE);
}

int	check_state(void)
{
	if (g_request.interrupt_heredocument)
		rl_done = 1;
	return (0);
}

t_result	readline_input_heredoc(char **heredoc, char *delimiter)
{
	char	*input;

	input = NULL;
	free_set((void **)heredoc, NULL);
	rl_event_hook = check_state;
	while (g_request.interrupt_heredocument == FALSE)
	{
		input = readline("> ");
		if (can_exit_heredocument(input, delimiter))
			break ;
		*heredoc = update_heredoc(heredoc, input);
		free_set((void **)&input, NULL);
	}
	rl_event_hook = NULL;
	free_set((void **)&input, NULL);
	return (SUCCESS);
}
