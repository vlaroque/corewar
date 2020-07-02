/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_useless.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljigmon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 00:50:00 by aljigmon          #+#    #+#             */
/*   Updated: 2020/06/21 15:24:41 by aljigmon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	count_words(const char *s, int i)
{
	int	count;

	if (s == NULL)
		return (0);
	count = 0;
	while (s[i])
	{
		while (s[i] == ',' || s[i] == '\t' || s[i] == '\n' || s[i] == ' ')
			i++;
		if (s[i] != ',' && s[i] != '\t' && s[i] != '\n' && s[i] != ' ' && s[i])
			count++;
		if (s[i] == '"')
		{
			i++;
			while (s[i] && s[i] != '"')
				i++;
			i++;
		}
		else
			while (s[i] != ',' && s[i] != ' '
					&& s[i] != '\t' && s[i] != '\n' && s[i])
				i++;
	}
	return (count);
}

static void	insert_them_2(char **tab, const char *s, int *a, int *i)
{
	int		j;

	j = 0;
	while (s[*i] == ',' || s[*i] == '\t' || s[*i] == '\n' || s[*i] == ' ')
		(*i)++;
	if (s[*i] == '"')
	{
		tab[*a][j++] = s[(*i)++];
		while (s[*i] && s[*i] != '"')
			tab[*a][j++] = s[(*i)++];
		if (s[*i] != '\0')
			tab[*a][j++] = s[(*i)++];
	}
	else
		while (s[*i] != ',' && s[*i] != '\t' && s[*i] != '\n' && s[*i] != ' '
				&& s[*i] != '\0')
			tab[*a][j++] = s[(*i)++];
	tab[*a][j] = '\0';
}

static char	**insert_them(char **tab, const char *s, int size)
{
	int	i;
	int	a;
	int	j;

	j = 0;
	a = 0;
	i = 0;
	if (tab == NULL || s == NULL)
		return (NULL);
	while (a < size)
	{
		insert_them_2(tab, s, &a, &i);
		a++;
	}
	return (tab);
}

char		**del_useless(char const *s)
{
	char	**tab;
	int		i;
	int		size;

	if (s == NULL)
		return (NULL);
	size = count_words(s, 0);
	i = 0;
	if ((tab = (char**)malloc(sizeof(char*) * size + 1)) == NULL)
		return (NULL);
	tab[size] = 0;
	while (i < size)
	{
		if (!(tab[i] = (char*)malloc(sizeof(char) * (ft_strlen(s) + 1))))
		{
			i--;
			while (i > -1)
				free(tab[i--]);
			free(tab);
			return (NULL);
		}
		i++;
	}
	return (insert_them(tab, s, size));
}
