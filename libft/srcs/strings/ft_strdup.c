/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 21:12:16 by axbrisse          #+#    #+#             */
/*   Updated: 2022/12/08 13:42:08 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	const size_t	bytes = ft_strlen(s) + 1;
	char			*dest;

	dest = malloc(sizeof(char) * bytes);
	if (dest != NULL)
		ft_strlcpy(dest, s, bytes);
	return (dest);
}
