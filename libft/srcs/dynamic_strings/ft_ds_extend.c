/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ds_extend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 10:11:09 by axbrisse          #+#    #+#             */
/*   Updated: 2023/02/24 20:57:56 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	ft_ds_extend(t_dynamic_string *s1, char *s2, size_t len2)
{
	size_t	i;

	i = 0;
	while (i < len2 && s2[i] != '\0')
	{
		if (!ft_ds_append(s1, s2[i]))
			return (false);
		++i;
	}
	return (true);
}
