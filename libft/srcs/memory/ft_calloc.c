/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 20:32:10 by axbrisse          #+#    #+#             */
/*   Updated: 2023/01/07 01:43:56 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	const size_t	bytes = nmemb * size;
	void			*ptr;

	if (size > 0 && nmemb > SIZE_MAX / size)
		return (NULL);
	ptr = malloc(bytes);
	if (ptr != NULL)
		ft_bzero(ptr, bytes);
	return (ptr);
}
