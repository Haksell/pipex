/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_get.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 14:07:43 by axbrisse          #+#    #+#             */
/*   Updated: 2022/12/25 14:09:56 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_lst_get(const t_list *lst, size_t idx)
{
	while (true)
	{
		if (lst == NULL)
			return (NULL);
		if (idx == 0)
			return (lst->content);
		lst = lst->next;
		--idx;
	}
}
