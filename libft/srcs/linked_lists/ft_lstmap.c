/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 20:55:30 by axbrisse          #+#    #+#             */
/*   Updated: 2022/11/09 21:16:05 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*cur;
	t_list	*next;

	if (lst == NULL || f == NULL || del == NULL)
		return (NULL);
	next = ft_lstmap(lst->next, f, del);
	if (next == NULL && lst->next != NULL)
		return (NULL);
	cur = ft_lstnew(f(lst->content));
	if (cur == NULL)
		ft_lstclear(&next, del);
	else
		cur->next = next;
	return (cur);
}
