/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 19:37:20 by axbrisse          #+#    #+#             */
/*   Updated: 2022/12/09 09:28:50 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_min(size_t n1, size_t n2)
{
	if (n1 < n2)
		return (n1);
	else
		return (n2);
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	const size_t	true_len = get_min(len, ft_strlen(big));
	const size_t	n = ft_strlen(little);
	size_t			i;

	i = 0;
	while (i + n <= true_len)
	{
		if (ft_strncmp(big + i, little, n) == 0)
			return ((char *)(big + i));
		i++;
	}
	return (NULL);
}
