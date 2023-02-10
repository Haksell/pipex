/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_num_words.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 00:23:34 by axbrisse          #+#    #+#             */
/*   Updated: 2023/01/07 03:21:15 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_num_words(char const *s, char const *set)
{
	bool	last_is_separator;
	size_t	res;
	size_t	i;

	last_is_separator = true;
	res = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (ft_strchr(set, s[i]) != NULL)
			last_is_separator = true;
		else
		{
			if (last_is_separator)
				++res;
			last_is_separator = false;
		}
		++i;
	}
	return (res);
}
