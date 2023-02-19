/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_arr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 10:43:27 by axbrisse          #+#    #+#             */
/*   Updated: 2023/02/19 09:12:44 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	full_strlen(int size, char **strs, char *sep)
{
	size_t	res;
	int		i;

	if (size == 0)
		return (0);
	res = ft_strlen(sep) * (size - 1);
	i = 0;
	while (i < size)
	{
		res += ft_strlen(strs[i]);
		i++;
	}
	return (res);
}

char	*ft_strjoin_arr(int size, char **strs, char *sep)
{
	char	*joined;
	int		length;
	int		arr_idx;
	int		full_idx;

	length = full_strlen(size, strs, sep);
	joined = malloc(sizeof(char) * (length + 1));
	if (joined == NULL)
		return (NULL);
	arr_idx = 0;
	full_idx = 0;
	while (arr_idx < size)
	{
		full_idx += ft_strlcpy(joined + full_idx, strs[arr_idx], length + 1);
		if (arr_idx < size - 1)
			full_idx += ft_strlcpy(joined + full_idx, sep, length + 1);
		arr_idx++;
	}
	joined[length] = '\0';
	return (joined);
}
