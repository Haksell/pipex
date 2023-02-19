/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wesh.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 12:26:09 by axbrisse          #+#    #+#             */
/*   Updated: 2023/02/19 12:29:13 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ctype.h>
#include <stdio.h>

int	main(int argc, char **argv)
{
	int	i;

	(void)argc;
	i = 0;
	while (argv[1][i] != '\0')
	{
		putchar(toupper(argv[1][i]));
		++i;
	}
	putchar('\n');
	return (argc);
}