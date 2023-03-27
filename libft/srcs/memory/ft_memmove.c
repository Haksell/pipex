/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 14:28:51 by axbrisse          #+#    #+#             */
/*   Updated: 2023/03/27 23:59:39 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*ft_memcpy_reverse(void *dest, const void *src, size_t n)
{
	int	i;

	if (dest == NULL || src == NULL)
		return (NULL);
	i = n - 1;
	while (i >= 0)
	{
		((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
		i--;
	}
	return (dest);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	static void	*(*funcs[])(void *, const void *, size_t) = {
		ft_memcpy,
		ft_memcpy_reverse
	};

	return (funcs[dest > src](dest, src, n));
}
