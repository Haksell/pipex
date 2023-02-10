/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ds_append.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 10:11:09 by axbrisse          #+#    #+#             */
/*   Updated: 2023/01/06 21:35:10 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	ft_ds_append(t_dynamic_string *s1, char c)
{
	char			*new_content;

	if (s1->length + 1 == s1->capacity)
	{
		s1->capacity <<= 1;
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
	s1->content[s1->length] = c;
	s1->content[s1->length + 1] = '\0';
	++s1->length;
	return (true);
}
