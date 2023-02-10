/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 20:46:43 by axbrisse          #+#    #+#             */
/*   Updated: 2023/02/09 20:46:49 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin3(char const *s1, char const *s2, char const *s3)
{
	const size_t	n1 = ft_strlen(s1);
	const size_t	n2 = ft_strlen(s2);
	const size_t	n3 = ft_strlen(s3);
	const size_t	bytes = n1 + n2 + n3 + 1;
	char			*joined;

	joined = malloc(bytes);
	if (joined == NULL)
		return (NULL);
	ft_strlcpy(joined, s1, n1 + 1);
	ft_strlcpy(joined + n1, s2, n2 + 1);
	ft_strlcpy(joined + n1 + n2, s3, n3 + 1);
	return (joined);
}
