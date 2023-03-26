/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_arr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 10:43:27 by axbrisse          #+#    #+#             */
/*   Updated: 2023/03/01 04:45:43 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	full_strlen(char **strs, char *sep, char *end)
{
	const int	sep_len = ft_strlen(sep);
	int			res;
	int			i;

	res = ft_strlen(end);
	if (strs[0] == NULL)
		return (res);
	i = 0;
	while (strs[i] != NULL)
	{
		res += ft_strlen(strs[i]);
		if (i != 0)
			res += sep_len;
		++i;
	}
	return (res);
}

char	*ft_strjoin_arr(char **strs, char *sep, char *end)
{
	char	*joined;
	int		length;
	int		arr_idx;
	int		full_idx;

	length = full_strlen(strs, sep, end);
	joined = malloc(sizeof(char) * (length + 1));
	if (joined == NULL)
		return (NULL);
	arr_idx = 0;
	full_idx = 0;
	while (strs[arr_idx] != NULL)
	{
		full_idx += ft_strlcpy(joined + full_idx, strs[arr_idx], length + 1);
		if (strs[arr_idx + 1] != NULL)
			full_idx += ft_strlcpy(joined + full_idx, sep, length + 1);
		++arr_idx;
	}
	ft_strlcpy(joined + full_idx, end, length + 1);
	return (joined);
}
