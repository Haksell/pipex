/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 14:42:48 by axbrisse          #+#    #+#             */
/*   Updated: 2023/03/13 17:09:29 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putendl_fd(char *s, int fd)
{
	char	*full;
	int		written;

	full = ft_strjoin(s, "\n");
	if (full == NULL)
		return (-1);
	written = ft_putstr_fd(full, fd);
	free(full);
	return (written);
}
