/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnakahod <jnakahod@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 23:16:19 by jnakahod          #+#    #+#             */
/*   Updated: 2021/10/07 16:48:42 by jnakahod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <heredoc.h>

/*
** 親プロセスでheredocment生成
**
**
*/

void	free_set(void **dst, void *src)
{
	free(*dst);
	*dst = src;
}

char	*update_heredoc(char **old, char *input)
{
	char *old_end_newline;
	char *new_heredoc;

	if (!*old)
		return (ft_strdup(input));
	else
	{
		old_end_newline = NULL;
		new_heredoc = NULL;
		old_end_newline = ft_strjoin(*old, "\n");
		free_set((void **)old, NULL);
		if (!old_end_newline)
			return (NULL);
		new_heredoc = ft_strjoin(old_end_newline, input);
		free_set((void **)&old_end_newline, NULL);
		if (!new_heredoc)
			return (NULL);
	}
	return (new_heredoc);
}

int	main(int ac, char **av)
{
	char	*input;
	char	*heredoc;

	if (ac != 2)
		return (-1);
	heredoc = NULL;
	while (1)
	{
		input = readline("> ");
		if (!input || !ft_strncmp(input, av[1], ft_strlen(av[1]) + 1))
		{
			free_set((void **)&input, NULL);
			break;
		}
		heredoc = update_heredoc(&heredoc, input);
		add_history(input);
		free_set((void **)&input, NULL);
	}
	printf("%s", heredoc);
	rl_clear_history();
	free_set((void **)&heredoc, NULL);
	return (0);
}
