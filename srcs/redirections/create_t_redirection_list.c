/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_t_redirection_list.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnakahod <jnakahod@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 10:39:15 by jnakahod          #+#    #+#             */
/*   Updated: 2021/09/21 18:46:53by jnakahod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <redirect.h>


int	get_num(char *str)
{
	int	num;

	num = 0;
	while(ft_isdigit(*str))
	{
		num = *str - '0' * num * 10;
		str++;
	}
	return (num);
}

int	find_redirection_to_match(char **str)
{
	int	i;
	int	type;

	i = 2;
	type = -1;
	if (!ft_strncmp(*str, "<<", 2))
		type = HEREDOC;
	else if (!ft_strncmp(*str, ">>", 2))
		type = APPEND;
	else if (!ft_strncmp(*str, "<", 1))
	{
		i = 1;
		type = INPUT;
	}
	else if (!ft_strncmp(*str, ">", 1))
	{
		i = 1;
		type = OUTPUT;
	}
	*str += i;
	return (type);
}
bool	is_white(int c)
{
	return (c == ' ' || ('\t' <= c && c <= '\r'));
}

//file名の長さ確認
char	*new_file_path(char **str)
{
	char	*path;
	int		i;

	if (!**str)
		return (NULL);
	//strがヌル文字になるまでインクリメントする
	i = 0;
	while ((*str)[i] && !is_white((*str)[i]))
		i++;
	path = (char *)malloc(sizeof(char) * (i + 1));
	if (!path)
		return (NULL);
	ft_strlcpy(path, *str, i + 1);
	*str += i;
	return (path);
}

t_redirection_list	*create_t_rd_list(int fd, int type, char *file_path)
{
	t_redirection_list	*res;

	(void)fd;
	res = (t_redirection_list *)malloc(sizeof(t_redirection_list) * 1);
	if (!res)
		return (NULL);
	if (type == INPUT)
		res->fd = 0;
	else if (type == OUTPUT)
		res->fd = 1;
	res->type = type;
	res->file_path = file_path;
	res->next = NULL;
	return (res);
}

void	add_node_to_rd_list(t_redirection_list **first, t_redirection_list *node)
{
	t_redirection_list	*tmp;

	if (!*first)
		*first = node;
	else
	{
		tmp = *first;
		while(tmp->next)
			tmp = tmp->next;
		tmp->next = node;
	}
}


int	create_t_redirection_list(char *rd_str, t_command *cmd)
{
	int		fd;
	int		type;
	char	*file_path;
	char	*str;
	char	*first;
	t_redirection_list *node;

	str = ft_strdup(rd_str);
	if (!str)
		return (-1);
	first = str;
	fd = -1;
	while(*str)
	{
		while (is_white(*str))
			str++;
		if (ft_isdigit(*str))
			fd = get_num(str);
		while (is_white(*str))
			str++;
		// type設定
		type = find_redirection_to_match(&str);
		while (is_white(*str))
			str++;
		// filepath 設定
		file_path = new_file_path(&str);
		while (is_white(*str))
			str++;
		// redirection_list 作成
		node = create_t_rd_list(fd, type, file_path);
		// append cmd->*_rd
		if (type == INPUT)
			add_node_to_rd_list(&(cmd->input_rd), node);
		else if (type == OUTPUT || type == APPEND)
			add_node_to_rd_list(&(cmd->output_rd), node);
		while(*str && is_white(*str))
			str++;
	}
	free(first);
	return (0);
}
