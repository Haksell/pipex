/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_endswith.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 17:35:36 by axbrisse          #+#    #+#             */
/*   Updated: 2023/01/20 14:42:30 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	ft_endswith(const char *str, const char *end)
{
	const size_t	len_str = ft_strlen(str);
	const size_t	len_end = ft_strlen(end);

	return (
		len_str >= len_end
		&& ft_strcmp(str + len_str - len_end, end) == 0
	);
}
