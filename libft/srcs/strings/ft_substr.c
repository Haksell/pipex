/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 21:43:15 by axbrisse          #+#    #+#             */
/*   Updated: 2022/12/08 13:53:58 by axbrisse         ###   ########.fr       */
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

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	s_len;
	size_t	bytes;
	char	*dest;

	if (s == NULL)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_strdup(""));
	bytes = get_min(s_len - start, len) + 1;
	dest = malloc(bytes);
	if (dest != NULL)
		ft_strlcpy(dest, s + start, bytes);
	return (dest);
}
