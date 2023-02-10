/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putbase_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 08:50:38 by axbrisse          #+#    #+#             */
/*   Updated: 2022/12/12 09:11:01 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putbase_fd(unsigned long n, char *base, size_t base_length, int fd)
{
	if (n < base_length)
		return (ft_putchar_fd(base[n], fd));
	else
		return (
			ft_putbase_fd(n / base_length, base, base_length, fd)
			+ ft_putchar_fd(base[n % base_length], fd)
		);
}
