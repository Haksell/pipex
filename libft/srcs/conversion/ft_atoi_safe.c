/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_safe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 02:42:17 by axbrisse          #+#    #+#             */
/*   Updated: 2022/12/25 02:42:31 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	ft_atoi_safe(char *s, int *n)
{
	unsigned long	absolute;
	int				sign;
	size_t			i;

	sign = 1;
	i = 0;
	if (s[0] == '-')
	{
		++i;
		sign = -1;
	}
	if (s[i] == '\0')
		return (false);
	absolute = 0;
	while (s[i] != '\0')
	{
		if (s[i] < '0' || s[i] > '9')
			return (false);
		absolute = 10 * absolute + s[i] - '0';
		if (absolute > 2147483648 - (sign == 1))
			return (false);
		++i;
	}
	*n = absolute * sign;
	return (true);
}
