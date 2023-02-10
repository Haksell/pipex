/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 13:24:06 by axbrisse          #+#    #+#             */
/*   Updated: 2022/12/09 08:52:42 by axbrisse         ###   ########.fr       */
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

static unsigned int	get_length(unsigned int absolute)
{
	unsigned int	length;

	length = 0;
	while (absolute > 0)
	{
		length++;
		absolute /= 10;
	}
	return (length);
}

static void	ft_itoa_recursive(unsigned int absolute, char *result)
{
	if (absolute == 0)
		return ;
	*result = absolute % 10 + 48;
	ft_itoa_recursive(absolute / 10, result - 1);
}

char	*ft_itoa(int n)
{
	const unsigned int	absolute = get_abs(n);
	const bool			is_negative = n < 0;
	const int			total_size = get_length(absolute) + is_negative;
	char				*result;

	if (n == 0)
		return (ft_strdup("0"));
	result = malloc(total_size + 1);
	if (result == NULL)
		return (NULL);
	result[total_size] = '\0';
	if (is_negative)
		result[0] = '-';
	ft_itoa_recursive(absolute, result + total_size - 1);
	return (result);
}
