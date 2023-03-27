/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_double.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 05:46:37 by axbrisse          #+#    #+#             */
/*   Updated: 2023/03/27 05:46:38 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_double(void ***ptr)
{
	size_t	i;
	void	**arr;

	if (*ptr == NULL)
		return ;
	arr = *ptr;
	i = 0;
	while (arr[i] != NULL)
	{
		ft_free(arr + i);
		++i;
	}
	ft_free((void **)ptr);
}
