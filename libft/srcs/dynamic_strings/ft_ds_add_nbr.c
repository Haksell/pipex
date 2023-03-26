/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ds_add_nbr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 23:48:32 by axbrisse          #+#    #+#             */
/*   Updated: 2023/02/25 23:51:35 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	ft_ds_add_nbr(t_dynamic_string *buffer, int n)
{
	return (ft_ds_extend_free(buffer, ft_itoa(n)));
}
