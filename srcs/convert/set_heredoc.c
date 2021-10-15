/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnakahod <jnakahod@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 23:50:02 by jnakahod          #+#    #+#             */
/*   Updated: 2021/10/09 15:33:25by jnakahod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

static void	free_set(void **dst, void *src)
{
	free(*dst);
	*dst = src;
}

size_t	count_non_quotes(char *str)
{
	size_t	size;
	int		i;

	size = 0;
	i = -1;
	while (str[++i])
		if(!is_quote(str[i]))
			size += 1;
	return (size);
}

void	rm_quote(char **str)
{
	char	*str_without_quots;
	int		i;
	int		index;
	size_t	len;

	len = count_non_quotes(*str);
	if (!len)
		return ;
	else
	{
		i = -1;
		index = -1;
		str_without_quots = (char *)ft_calloc(len + 1, sizeof(char));
		while ((*str)[++i])
		{
			if (!is_quote((*str)[i]))
				str_without_quots[++index] = (*str)[i];
		}
		free_set((void **)str, (void *)str_without_quots);
	}
}

char	*update_heredoc(char **old, char *input)
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

t_bool	is_match_delimiter(char *input, char *delimiter)
{
	if (!ft_strncmp(input, delimiter, ft_strlen(delimiter) + 1))
		return (TRUE);
	return (FALSE);
}

t_bool is_str_has_closed_quarts(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (is_quote(str[i]))
			if (find_closing_qt(str, &i))
				return(TRUE);
	}
	return (FALSE);
}

t_bool	is_dollar(char c)
{
	if (c == DLL)
		return (TRUE);
	else
		return (FALSE);
}

t_bool is_env_end_in_heredoc(char c)
{
  return (c == '\0' || c == '\n' || c == DLL || c == SPC || c == SLSH || c == QSTN || is_quote(c));
}

char	*get_env_key_in_heredoc(char **heredoc)
{
	int		env_index;
	char	*key;

	if (!**heredoc)
		return (NULL);
	env_index = 0;
	key = NULL;
	while (!is_env_end_in_heredoc((*heredoc)[env_index]))
		env_index++;
	if ((*heredoc)[env_index] == QSTN)
		env_index++;
	if (env_index > 0)
		key = ft_strndup(*heredoc, env_index);
	*heredoc += env_index;
	return (key);
}

t_result	expand_heredoc(char **contents)
{
	int		i;
	char	*pre_str;
	char	*key;
	char	*value;
	char	*heredoc;
	char	*expanded_heredoc;

	if (!*contents)
		return (SUCCESS);
	i = 0;
	heredoc = *contents;
	expanded_heredoc = NULL;
	while(heredoc[i])
	{
		if (is_dollar(heredoc[i]))
		{
			/* $までをstrndup */
			pre_str = ft_strndup(heredoc, i);
			free_set((void **)&expanded_heredoc, (void *)ft_strjoin(expanded_heredoc, pre_str));
			i++;
			heredoc += i;
			/* $以降からkey作成 */
			key = get_env_key_in_heredoc(&heredoc);
			/* keyからvalue生成 */
			value = get_env_value(key);
			/* $までとvalueをjoin */
			if (value)
				free_set((void **)&expanded_heredoc, (void *)ft_strjoin(expanded_heredoc, value));
			free_set((void **)&key, NULL);
			free_set((void **)&pre_str, NULL);
			free_set((void **)&value, NULL);
			i = -1;
		}
		i++;
	}
	if (i > 0)
	{
		pre_str = ft_strndup(heredoc, i);
		free_set((void **)&expanded_heredoc, (void *)ft_strjoin(expanded_heredoc, pre_str));
		free_set((void **)&pre_str, NULL);
	}
	free_set((void **)contents, (void *)expanded_heredoc);
	return (SUCCESS);
}

t_bool	can_expand_heredoc(char *delimiter)
{
	if (is_str_has_closed_quarts(delimiter))
		return (FALSE);
	else
		return (TRUE);
}

char	*rm_quotes(char *str)
{
	char *str_without_quots;
	int	i;
	int	index;
	size_t	len;

	len = count_non_quotes(str);
	if (!len)
		return (ft_strdup(str));
	else
	{
		i = -1;
		index = -1;
		str_without_quots = (char *)ft_calloc(len + 1, sizeof(char));
		while (str[++i])
		{
			if (!is_quote(str[i]))
				str_without_quots[++index] = str[i];
		}
	}
	return (str_without_quots);
}

void	init_heredoc(t_heredoc_to_fd **heredoc)
{
	*heredoc = (t_heredoc_to_fd *)ft_calloc(1, sizeof(t_heredoc_to_fd));
	(*heredoc)->contents = NULL;
	(*heredoc)->tmp_fd = -1;
	(*heredoc)->tmp_file_path = NULL;
}

t_bool	can_exit_heredocument(char *input, char *delimiter)
{
	if (!input || is_match_delimiter(input, delimiter))
		return (TRUE);
	else
		return (FALSE);

}

t_result	readline_input_heredoc(char **heredoc, char *delimiter)
{
	char	*input;

	input = NULL;
	free_set((void **)heredoc, NULL);
	while (TRUE)
	{
		input = readline("> ");
		if (can_exit_heredocument(input, delimiter))
			break ;
		*heredoc = update_heredoc(heredoc, input);
		free_set((void **)&input, NULL);
	}
	free_set((void **)&input, NULL);
	return (SUCCESS);
}

void	set_heredocument(t_pipe_list **node)
{
	t_redirection_list	*tmp_input;
	t_demi_for_heredoc	*tmp_demi;
	t_bool				expantable_heredoc;
	t_heredoc_to_fd		**heredoc;
	char				*delimiter;

	if (!(*node))
		return ;
	tmp_input = (*node)->input_rd;
	heredoc = &(*node)->heredoc;
	while (tmp_input)
	{
		if (tmp_input->type == HEREDOC)
		{
			if (!(*heredoc))
				init_heredoc(heredoc);
			tmp_demi = tmp_input->demi_heredoc;
			expantable_heredoc = can_expand_heredoc(tmp_demi->delimiter);
			delimiter = rm_quotes(tmp_demi->delimiter);
			readline_input_heredoc(&(*heredoc)->contents, delimiter);
			if (expantable_heredoc)
				expand_heredoc(&(*heredoc)->contents);
			free_set((void **)&delimiter, NULL);
		}
		tmp_input = tmp_input->next;
	}
	tmp_demi->last_heredoc = TRUE;
}
