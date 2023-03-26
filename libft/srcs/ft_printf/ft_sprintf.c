/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 14:13:37 by axbrisse          #+#    #+#             */
/*   Updated: 2023/02/26 14:15:45 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_sprintf(const char *format, ...)
{
	va_list	ap;
	char	*content;

	va_start(ap, format);
	content = ft_vsprintf(format, ap);
	va_end(ap);
	return (content);
}
