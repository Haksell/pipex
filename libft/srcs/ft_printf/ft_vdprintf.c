/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vdprintf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 23:41:07 by axbrisse          #+#    #+#             */
/*   Updated: 2023/02/26 14:22:33 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_vdprintf(int fd, const char *format, va_list ap)
{
	char	*content;
	int		written;

	content = ft_vsprintf(format, ap);
	if (content == NULL)
		return (-1);
	written = write(fd, content, ft_strlen(content));
	free(content);
	return (written);
}
