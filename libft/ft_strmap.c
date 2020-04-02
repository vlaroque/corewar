/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaroque <vlaroque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 14:18:09 by vlaroque          #+#    #+#             */
/*   Updated: 2018/11/24 11:38:55 by vlaroque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*result_str;
	int		i;

	i = 0;
	if (s == NULL || f == NULL)
		return (NULL);
	if (!(result_str = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1))))
		return (NULL);
	while (s[i])
	{
		result_str[i] = f(s[i]);
		i++;
	}
	result_str[i] = '\0';
	return (result_str);
}
