/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 13:39:00 by axbrisse          #+#    #+#             */
/*   Updated: 2023/03/01 17:34:58 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lst_sort(t_list *lst, int (*cmp)(void *, void *))
{
	const int	size = ft_lstsize(lst);
	t_list		*curr;
	int			i;
	void		*tmp;

	i = 1;
	while (i < size)
	{
		curr = lst;
		while (curr && curr->next)
		{
			if (cmp(curr->content, curr->next->content) > 0)
			{
				tmp = curr->next->content;
				curr->next->content = curr->content;
				curr->content = tmp;
			}
			curr = curr->next;
		}
		++i;
	}
}
