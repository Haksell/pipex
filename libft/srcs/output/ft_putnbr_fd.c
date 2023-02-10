/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 14:46:50 by axbrisse          #+#    #+#             */
/*   Updated: 2022/12/12 09:32:24 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_fd(int n, int fd)
{
	if (n < 0)
		return (
			ft_putchar_fd('-', fd)
			+ ft_putbase_fd(-(unsigned long)n, DECIMAL, 10, fd)
		);
	else
		return (ft_putbase_fd(n, DECIMAL, 10, fd));
}
