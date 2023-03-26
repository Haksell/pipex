/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 08:51:07 by axbrisse          #+#    #+#             */
/*   Updated: 2023/02/25 23:54:19 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	ssize_t	written;

	va_start(ap, format);
	written = ft_vdprintf(STDOUT_FILENO, format, ap);
	va_end(ap);
	return (written);
}
