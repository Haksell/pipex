/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_triple.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 05:45:03 by axbrisse          #+#    #+#             */
/*   Updated: 2023/03/27 05:46:19 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_triple(void ****ptr)
{
	size_t	i;
	void	***arr;

	if (*ptr == NULL)
		return ;
	arr = *ptr;
	i = 0;
	while (arr[i] != NULL)
	{
		ft_free_double(arr + i);
		++i;
	}
	ft_free((void **)ptr);
}
