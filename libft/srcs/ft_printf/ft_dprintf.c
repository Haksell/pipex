/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 23:53:45 by axbrisse          #+#    #+#             */
/*   Updated: 2023/02/25 23:59:37 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_dprintf(int fd, const char *format, ...)
{
	va_list	ap;
	ssize_t	written;

	va_start(ap, format);
	written = ft_vdprintf(fd, format, ap);
	va_end(ap);
	return (written);
}
