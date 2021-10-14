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

int count_size_of_delimiters(t_redirection_list *node, t_demi_for_heredoc **last_demi_heredoc)
{
	t_redirection_list *tmp;
	int					size_delimiters;

	tmp = node;
	size_delimiters = 0;
	while (tmp)
	{
		if (tmp->type == HEREDOC)
		{
			size_delimiters++;
			*last_demi_heredoc = tmp->demi_heredoc;
		}
		tmp = tmp->next;
	}
	if (*last_demi_heredoc)
		(*last_demi_heredoc)->last_heredoc = TRUE;
	return (size_delimiters);
}

void	*free_delimiters(char ***delimiters, int size)
{
	int	i;

	i = -1;
	while (++i < size)
		free_set((void **)&(*delimiters)[i], NULL);
	free(*delimiters);
	*delimiters = NULL;
	return (NULL);
}

char	**create_delimiters_array(t_redirection_list *rd_list, int size_array)
{
	char				**delimiters;
	int					i;
	t_redirection_list	*tmp;

	delimiters = (char **)malloc(sizeof(char *) * (size_array + 1));
	if (!delimiters)
		return (NULL);
	tmp = rd_list;
	i = 0;
	while (tmp)
	{
		if (tmp->type == HEREDOC)
		{
			delimiters[i] = ft_strdup(tmp->demi_heredoc->delimiter);
			if (!delimiters[i])
				return (free_delimiters(&delimiters, i));
			i++;
		}
		tmp = tmp->next;
	}
	delimiters[i] = NULL;
	return (delimiters);
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

t_bool	can_update_heredoc(char *input, char **delimiters, int *i, int last_index)
{
	int	update_start_index;

	update_start_index = last_index - 1;

	if (last_index == 0)
		return (TRUE);
	else if (is_match_delimiter(input, delimiters[*i]))
	{
		if (*i == update_start_index)
			return (TRUE);
		(*i)++;
	}
	return (FALSE);
}

t_bool	can_exit_heredocument(char *input, t_bool updatable, char *last_delimiter)
{
	if (!input || (updatable && is_match_delimiter(input, last_delimiter)))
		return (TRUE);
	else
		return (FALSE);
}

char	*readline_input_heredoc(char **delimiters, int	size_of_array)
{
	char	*heredoc;
	char	*input;
	int		i;
	int		last_index;
	t_bool	updatable;

	heredoc = NULL;
	input = NULL;
	i = 0;
	last_index = size_of_array - 1;
	if (last_index == 0)
		updatable = TRUE ;
	else
		updatable = FALSE;
	while (TRUE)
	{
		input = readline("> ");
		if (can_exit_heredocument(input, updatable, delimiters[last_index]))
			break;
		if (updatable)
			heredoc = update_heredoc(&heredoc, input);
		else
			updatable = can_update_heredoc(input, delimiters, &i, last_index);
		free_set((void **)&input, NULL);
	}
	free_set((void **)&input, NULL);
	return (heredoc);
}

void	init_heredoc_to_fd(t_heredoc_to_fd *heredoc)
{
	heredoc->contents = NULL;
	heredoc->tmp_fd = -1;
	heredoc->tmp_file_path = NULL;
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

char	*get_env_key_in_heredoc(char **heredoc, int *i)
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
			key = get_env_key_in_heredoc(&heredoc, &i);
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

t_bool	can_expantable_heredoc(char *delimiter)
{
	if (is_str_has_closed_quarts(delimiter))
		return (FALSE);
	else
		return (TRUE);
}

void	set_heredocument(t_pipe_list **node)
{
	t_demi_for_heredoc	*last_demi;
	int					size_of_delimiters;
	char				**delimiters;
	t_heredoc_to_fd		*heredoc;
	t_bool				expantable_heredoc;

	if (!(*node))
		return ;
	size_of_delimiters = 0;
	last_demi = NULL;
	size_of_delimiters = count_size_of_delimiters((*node)->input_rd, &last_demi);
	if (!size_of_delimiters)
		return ;
	expantable_heredoc = can_expantable_heredoc(last_demi->delimiter);
	delimiters = create_delimiters_array((*node)->input_rd, size_of_delimiters);
	(*node)->heredoc = (t_heredoc_to_fd *)malloc(sizeof(t_heredoc_to_fd));
	if (!(*node))
		return ;
	init_heredoc_to_fd((*node)->heredoc);
	heredoc = (*node)->heredoc;
	heredoc->contents = readline_input_heredoc(delimiters, size_of_delimiters);
	if (expantable_heredoc)
		expand_heredoc(&(*node)->heredoc->contents);
	free_delimiters(&delimiters, size_of_delimiters);
}
