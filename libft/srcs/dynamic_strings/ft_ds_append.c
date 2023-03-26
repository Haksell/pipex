/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ds_append.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 10:11:09 by axbrisse          #+#    #+#             */
/*   Updated: 2023/03/03 00:32:42 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	ft_ds_append(t_dynamic_string *ds, char c)
{
	char			*new_content;

	if (ds->length + 1 == ds->capacity)
	{
		ds->capacity <<= 1;
		new_content = malloc(ds->capacity);
		if (new_content == NULL)
		{
			free(ds->content);
			return (false);
		}
		ft_strlcpy(new_content, ds->content, ds->length + 1);
		free(ds->content);
		ds->content = new_content;
	}
	ds->content[ds->length] = c;
	ds->content[ds->length + 1] = '\0';
	++ds->length;
	return (true);
}
