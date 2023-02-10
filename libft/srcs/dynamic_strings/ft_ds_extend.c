/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ds_extend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 10:11:09 by axbrisse          #+#    #+#             */
/*   Updated: 2022/12/09 10:52:17 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_max(size_t n1, size_t n2)
{
	if (n1 > n2)
		return (n1);
	else
		return (n2);
}

bool	ft_ds_extend(t_dynamic_string *s1, char *s2, size_t len2)
{
	const size_t	required_capacity = s1->length + len2 + 1;
	char			*new_content;

	if (required_capacity > s1->capacity)
	{
		s1->capacity = get_max(required_capacity, 2 * s1->capacity);
		new_content = malloc(s1->capacity);
		if (new_content == NULL)
		{
			free(s1->content);
			return (false);
		}
		ft_strlcpy(new_content, s1->content, s1->length + 1);
		free(s1->content);
		s1->content = new_content;
	}
	ft_strlcpy(s1->content + s1->length, s2, len2 + 1);
	s1->length += len2;
	return (true);
}
