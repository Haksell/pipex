/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ds_add_nbr_base.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 23:49:06 by axbrisse          #+#    #+#             */
/*   Updated: 2023/02/25 23:49:39 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	ft_ds_add_nbr_base(
	t_dynamic_string *buffer,
	unsigned long n,
	char *base
)
{
	return (ft_ds_extend_free(buffer, ft_itoa_base(n, base)));
}
