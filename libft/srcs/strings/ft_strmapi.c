/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 13:57:35 by axbrisse          #+#    #+#             */
/*   Updated: 2022/12/08 14:26:28 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	size_t	n;
	char	*t;

	if (f == NULL)
		return (ft_strdup(s));
	n = ft_strlen(s);
	t = malloc(n + 1);
	if (t == NULL)
		return (NULL);
	i = 0;
	while (i < n)
	{
		t[i] = f(i, s[i]);
		i++;
	}
	t[n] = '\0';
	return (t);
}
