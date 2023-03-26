/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 21:49:23 by axbrisse          #+#    #+#             */
/*   Updated: 2023/02/24 22:01:35 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_length(unsigned long n, size_t base_length)
{
	size_t	length;

	length = 0;
	while (n > 0)
	{
		++length;
		n /= base_length;
	}
	return (length);
}

static void	ft_itoa_recursive(
	unsigned long n, char *result,
	char *base, size_t base_length
)
{
	if (n == 0)
		return ;
	*result = base[n % base_length];
	ft_itoa_recursive(n / base_length, result - 1, base, base_length);
}

char	*ft_itoa_base(unsigned long n, char *base)
{
	const size_t		base_length = ft_strlen(base);
	const int			total_size = get_length(n, base_length);
	char				*result;

	if (n == 0)
		return (ft_substr(base, 0, 1));
	result = malloc(total_size + 1);
	if (result == NULL)
		return (NULL);
	result[total_size] = '\0';
	ft_itoa_recursive(n, result + total_size - 1, base, base_length);
	return (result);
}
