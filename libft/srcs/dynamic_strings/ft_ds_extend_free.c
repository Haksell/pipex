/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ds_extend_free.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 23:46:43 by axbrisse          #+#    #+#             */
/*   Updated: 2023/02/25 23:46:59 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	ft_ds_extend_free(t_dynamic_string *buffer, char *s)
{
	bool	result;

	if (s == NULL)
		return (false);
	result = ft_ds_extend(buffer, s, SIZE_MAX);
	free(s);
	return (result);
}
