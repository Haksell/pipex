/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 10:43:27 by axbrisse          #+#    #+#             */
/*   Updated: 2022/12/08 14:01:45 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	const size_t	n1 = ft_strlen(s1);
	const size_t	n2 = ft_strlen(s2);
	const size_t	bytes = n1 + n2 + 1;
	char			*joined;

	joined = malloc(bytes);
	if (joined == NULL)
		return (NULL);
	ft_strlcpy(joined, s1, n1 + 1);
	ft_strlcpy(joined + n1, s2, n2 + 1);
	return (joined);
}
