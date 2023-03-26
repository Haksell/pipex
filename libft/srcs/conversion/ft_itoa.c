/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 13:24:06 by axbrisse          #+#    #+#             */
/*   Updated: 2023/02/24 22:06:04 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	get_abs(int n)
{
	if (n < 0)
		return (-n);
	else
		return (n);
}

char	*ft_itoa(int n)
{
	char	*absolute;
	char	*complete;

	absolute = ft_itoa_base(get_abs(n), DECIMAL);
	if (absolute == NULL || n >= 0)
		return (absolute);
	complete = ft_strjoin("-", absolute);
	free(absolute);
	return (complete);
}
