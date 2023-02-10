/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 13:39:00 by axbrisse          #+#    #+#             */
/*   Updated: 2022/12/25 14:00:48 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lst_sort(t_list *lst, int (*cmp)(void *, void *))
{
	const int	size = ft_lstsize(lst);
	t_list		*cur;
	int			i;
	void		*tmp;

	i = 1;
	while (i < size)
	{
		cur = lst;
		while (cur && cur->next)
		{
			if (cmp(cur->content, cur->next->content) > 0)
			{
				tmp = cur->next->content;
				cur->next->content = cur->content;
				cur->content = tmp;
			}
			cur = cur->next;
		}
		++i;
	}
}
