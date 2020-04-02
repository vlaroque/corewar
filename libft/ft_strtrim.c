/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaroque <vlaroque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 13:03:18 by vlaroque          #+#    #+#             */
/*   Updated: 2018/11/21 16:44:44 by vlaroque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	nothing(char c)
{
	if (c == ' ' || c == '\n' || c == '\t')
		return (1);
	return (0);
}

char		*ft_strtrim(char const *s)
{
	size_t	i;
	int		len;
	char	*str;

	i = 0;
	if (s == NULL)
		return (NULL);
	if (!(len = ft_strlen(s)))
		len = 1;
	while (len > 0 && nothing(s[len - 1]))
		len--;
	if (len == 0)
	{
		if ((str = ft_strnew(1)))
			str[0] = '\0';
		return (str);
	}
	while (s[i] && nothing(s[i]))
		i++;
	if (!(str = ft_strnew(len - i)))
		return (NULL);
	str = ft_strncpy(str, s + i, len - i);
	return (str);
}
