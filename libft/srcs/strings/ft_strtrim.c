/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 10:51:15 by axbrisse          #+#    #+#             */
/*   Updated: 2022/12/12 08:26:09 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	lo;
	size_t	hi;

	lo = 0;
	while (s1[lo] != '\0' && ft_strchr(set, s1[lo]))
		lo++;
	if (s1[lo] == '\0')
		return (ft_strdup(""));
	hi = ft_strlen(s1) - 1;
	while (s1[hi] != '\0' && ft_strchr(set, s1[hi]))
		hi--;
	return (ft_substr(s1, lo, hi - lo + 1));
}
