/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 17:35:36 by axbrisse          #+#    #+#             */
/*   Updated: 2023/03/13 17:11:26 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	const unsigned char	uc = (unsigned char)c;
	size_t				i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == uc)
			return ((char *)(s + i));
		i++;
	}
	if (uc == 0)
		return ((char *)(s + i));
	return (NULL);
}
