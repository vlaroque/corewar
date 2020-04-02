/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaroque <vlaroque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 12:09:23 by vlaroque          #+#    #+#             */
/*   Updated: 2018/11/20 18:39:38 by vlaroque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*typed_s;
	unsigned char	typed_c;
	size_t			i;

	typed_s = (unsigned char *)s;
	typed_c = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (typed_s[i] == typed_c)
			return ((void *)&typed_s[i]);
		i++;
	}
	return (NULL);
}
