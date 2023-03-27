/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_set.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 22:33:57 by axbrisse          #+#    #+#             */
/*   Updated: 2023/03/27 05:44:29 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_word_len(char const *s, char const *set)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0' && ft_strchr(set, s[i]) == NULL)
		++i;
	return (i);
}

static char	*add_word(char const *s, size_t *i, char const *set)
{
	const size_t	word_len = get_word_len(s + *i, set);
	const size_t	bytes = word_len + 1;
	char			*dest;

	dest = malloc(sizeof(char) * bytes);
	if (dest != NULL)
		ft_strlcpy(dest, s + *i, bytes);
	*i += word_len - 1;
	return (dest);
}

char	**ft_split_set(char const *s, char const *set)
{
	const size_t	num_words = ft_num_words(s, set);
	char			**words;
	size_t			arr_idx;
	size_t			i;

	words = ft_calloc(num_words + 1, sizeof(char *));
	if (words == NULL)
		return (NULL);
	words[num_words] = NULL;
	i = 0;
	arr_idx = 0;
	while (s[i] != '\0')
	{
		if (ft_strchr(set, s[i]) == NULL)
		{
			words[arr_idx] = add_word(s, &i, set);
			if (words[arr_idx] == NULL)
				ft_free_double((void ***)&words);
			if (words[arr_idx] == NULL)
				return (NULL);
			++arr_idx;
		}
		++i;
	}
	return (words);
}
