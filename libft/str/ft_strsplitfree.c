/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplitfree.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afoures <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 15:13:28 by afoures           #+#    #+#             */
/*   Updated: 2017/11/10 15:15:49 by afoures          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_strsplitfree(char const *s, char c)
{
	size_t			nb_words;
	size_t			len_word;
	t_index			index;
	char			**tab;

	if (!s)
		return (NULL);
	nb_words = ft_countword(s, c);
	if (!(tab = (char **)malloc(sizeof(char *) * nb_words + 1)))
		return (NULL);
	index = (t_index){-1, 0};
	while (s[++index.x] && index.y < nb_words)
	{
		len_word = 0;
		if (s[index.x] != c && s[index.x])
		{
			while (s[index.x + len_word] != c && s[index.x + len_word])
				len_word++;
			tab[index.y++] = ft_strsub(s, index.x, len_word);
			index.x += len_word;
		}
	}
	tab[index.y] = NULL;
	free((void *)s);
	return (tab);
}
