/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_double_pointer.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 22:24:08 by axbrisse          #+#    #+#             */
/*   Updated: 2023/02/07 13:11:07 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_double_pointer(void ***grid, size_t height)
{
	size_t	i;

	if (*grid == NULL)
		return ;
	i = 0;
	while (i < height && (*grid)[i] != NULL)
	{
		ft_free(&(*grid)[i]);
		++i;
	}
	ft_free((void **)grid);
}
