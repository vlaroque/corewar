/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stherkil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/13 18:43:15 by stherkil          #+#    #+#             */
/*   Updated: 2020/02/19 19:00:06 by vlaroque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strndup(const char *s1, int n)
{
	char *out;

	if (!(out = (char*)malloc(sizeof(char) * (n + 1))))
		return (NULL);
	ft_strncpy(out, s1, n);
	out[n] = '\0';
	return (out);
}
