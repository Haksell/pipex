/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:52:56 by axbrisse          #+#    #+#             */
/*   Updated: 2022/12/08 07:52:35 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	uc;
	size_t			i;

	uc = (unsigned char) c;
	i = 0;
	while (i < n)
	{
		((unsigned char *)s)[i] = uc;
		i++;
	}
	return (s);
}
