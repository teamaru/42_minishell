/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsugiyam <tsugiyam@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 16:55:25 by tsugiyam          #+#    #+#             */
/*   Updated: 2021/05/11 22:24:35 by tsugiyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "./libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*next;
	t_list	*new_list;
	t_list	**begin;

	new_list = NULL;
	begin = &new_list;
	while (lst)
	{
		ft_lstadd_back(begin, ft_lstnew(f(lst->content)));
		next = lst->next;
		if (del)
			ft_lstdelone(lst, del);
		lst = next;
	}
	return (new_list);
}
