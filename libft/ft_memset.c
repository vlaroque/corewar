/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaroque <vlaroque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/10 13:08:07 by vlaroque          #+#    #+#             */
/*   Updated: 2018/11/20 18:43:49 by vlaroque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*bytes;

	bytes = (unsigned char *)b;
	i = 0;
	while (i < len)
	{
		bytes[i] = (unsigned char)c;
		i++;
	}
	return ((void*)bytes);
}
