/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaroque <vlaroque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 13:24:30 by vlaroque          #+#    #+#             */
/*   Updated: 2018/11/24 11:36:06 by vlaroque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int		ft_isword(int i, char const *str, char c)
{
	if (str[i] != c && i == 0)
		return (1);
	else if (str[i] != c && str[i - 1] == c)
		return (1);
	else
		return (0);
}

static int		ft_wordlen(int beg, char const *str, char c)
{
	int i;

	i = 0;
	while (str[beg + i] && str[beg + i] != c)
		i++;
	return (i);
}

char			**ft_strsplit(char const *s, char c)
{
	size_t	i;
	size_t	wordlen;
	size_t	words;
	char	**tab;

	if (s == NULL)
		return (NULL);
	if (!(tab = (char **)malloc(sizeof(*tab) * (ft_countwords(s, c) + 1))))
		return (NULL);
	i = -1;
	words = 0;
	while (s[++i])
		if (ft_isword(i, s, c))
		{
			wordlen = ft_wordlen(i, s, c);
			if (!(tab[words] = ft_strnew(wordlen)))
			{
				ft_freechartab(&tab);
				return (NULL);
			}
			tab[words] = ft_strncpy(tab[words], s + i, wordlen);
			words++;
		}
	tab[words] = NULL;
	return (tab);
}
