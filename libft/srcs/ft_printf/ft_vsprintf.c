/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vsprintf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 14:11:02 by axbrisse          #+#    #+#             */
/*   Updated: 2023/02/26 14:12:17 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static bool	write_ptr(t_dynamic_string *buffer, void *ptr)
{
	if (ptr == NULL)
		return (ft_ds_extend(buffer, "(nil)", SIZE_MAX));
	return (ft_ds_extend(buffer, "0x", SIZE_MAX)
		&& ft_ds_add_nbr_base(buffer, (unsigned long)ptr, HEXA_LOWER));
}

static bool	write_str(t_dynamic_string *buffer, char *s)
{
	if (s == NULL)
		return (ft_ds_extend(buffer, "(null)", SIZE_MAX));
	return (ft_ds_extend(buffer, s, SIZE_MAX));
}

static bool	convert(t_dynamic_string *buffer, char format_char, va_list ap)
{
	if (format_char == '%')
		return (ft_ds_append(buffer, '%'));
	else if (format_char == 'c')
		return (ft_ds_append(buffer, va_arg(ap, int)));
	else if (format_char == 's')
		return (write_str(buffer, va_arg(ap, char *)));
	else if (format_char == 'p')
		return (write_ptr(buffer, va_arg(ap, void *)));
	else if (format_char == 'd' || format_char == 'i')
		return (ft_ds_add_nbr(buffer, va_arg(ap, int)));
	else if (format_char == 'u')
		return (ft_ds_add_nbr_base(buffer, va_arg(ap, unsigned int), DECIMAL));
	else if (format_char == 'x')
		return (ft_ds_add_nbr_base(buffer, va_arg(ap, unsigned int),
				HEXA_LOWER));
	else if (format_char == 'X')
		return (ft_ds_add_nbr_base(buffer, va_arg(ap, unsigned int),
				HEXA_UPPER));
	return (false);
}

char	*ft_vsprintf(const char *format, va_list ap)
{
	t_dynamic_string	buffer;
	size_t				i;
	bool				success;

	buffer = ft_ds_new("");
	if (buffer.content == NULL)
		return (NULL);
	i = 0;
	while (format[i] != '\0')
	{
		if (format[i] == '%')
			success = convert(&buffer, format[++i], ap);
		else
			success = ft_ds_append(&buffer, format[i]);
		if (!success)
			return (free(buffer.content), NULL);
		i++;
	}
	return (buffer.content);
}
