/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 20:55:30 by axbrisse          #+#    #+#             */
/*   Updated: 2023/03/01 17:34:58 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*curr;
	t_list	*next;

	if (lst == NULL || f == NULL || del == NULL)
		return (NULL);
	next = ft_lstmap(lst->next, f, del);
	if (next == NULL && lst->next != NULL)
		return (NULL);
	curr = ft_lstnew(f(lst->content));
	if (curr == NULL)
		ft_lstclear(&next, del);
	else
		curr->next = next;
	return (curr);
}
