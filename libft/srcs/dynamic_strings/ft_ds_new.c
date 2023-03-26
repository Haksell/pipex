/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ds_new.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 10:00:38 by axbrisse          #+#    #+#             */
/*   Updated: 2023/03/01 03:04:04 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dynamic_string	ft_ds_new(char *s)
{
	t_dynamic_string	dynamic_string;

	if (s == NULL)
	{
		dynamic_string.content = NULL;
		dynamic_string.length = -1;
		dynamic_string.capacity = -1;
	}
	else
	{
		dynamic_string.content = ft_strdup(s);
		dynamic_string.length = ft_strlen(s);
		dynamic_string.capacity = dynamic_string.length + 1;
	}
	return (dynamic_string);
}
