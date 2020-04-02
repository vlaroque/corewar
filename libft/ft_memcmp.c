/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaroque <vlaroque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 12:35:22 by vlaroque          #+#    #+#             */
/*   Updated: 2018/11/20 18:40:38 by vlaroque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*typed_s1;
	unsigned char	*typed_s2;
	size_t			i;

	typed_s1 = (unsigned char *)s1;
	typed_s2 = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (typed_s1[i] != typed_s2[i])
			return ((int)(typed_s1[i] - typed_s2[i]));
		i++;
	}
	return (0);
}
