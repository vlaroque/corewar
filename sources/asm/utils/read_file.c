/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljigmon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/24 07:44:12 by aljigmon          #+#    #+#             */
/*   Updated: 2020/04/24 07:48:13 by aljigmon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static char		*joinstr(char *s1, char *s2, int f)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (s1 == NULL && s2 == NULL)
		return (NULL);
	else if (s1 == NULL || s2 == NULL)
		return (s1 == NULL ? ft_strdup(s2) : ft_strdup(s1));
	if (!(str = malloc(sizeof(*str) * (ft_strlen(s1) + ft_strlen(s2) + 1))))
		return (NULL);
	ft_memset(str, '\0', ft_strlen(s1) + ft_strlen(s2) + 1);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
		str[i++] = s2[j++];
	f ? ft_strdel(&s1) : NULL;
	return (str);
}

char			*read_file(const int fd)
{
	int		code;
	char	buf[PAGE_SIZE];
	char	*str;

	code = 0;
	str = NULL;
	ft_memset(buf, '\0', PAGE_SIZE);
	while ((code = read(fd, &buf, PAGE_SIZE)) > 0)
	{
		buf[code] = '\0';
		str = joinstr(str, buf, 1);
		if (!str)
			return (NULL);
		ft_memset(buf, '\0', PAGE_SIZE);
	}
	if (code == -1)
		return (NULL);
	return (str);
}
