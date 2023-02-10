/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_includes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 14:02:20 by axbrisse          #+#    #+#             */
/*   Updated: 2022/12/25 14:07:11 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	ft_lst_includes(const t_list *lst, void *x)
{
	while (lst != NULL)
	{
		if (lst->content == x)
			return (true);
		lst = lst->next;
	}
	return (false);
}
