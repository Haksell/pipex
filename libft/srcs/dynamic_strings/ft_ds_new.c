/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ds_new.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 10:00:38 by axbrisse          #+#    #+#             */
/*   Updated: 2023/01/06 21:09:08 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dynamic_string	ft_ds_new(char *s)
{
	const size_t		length = ft_strlen(s);
	t_dynamic_string	dynamic_string;

	dynamic_string.content = ft_strdup(s);
	dynamic_string.length = length;
	dynamic_string.capacity = length + 1;
	return (dynamic_string);
}
