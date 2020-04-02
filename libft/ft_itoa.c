/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaroque <vlaroque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 15:35:29 by vlaroque          #+#    #+#             */
/*   Updated: 2018/11/21 18:20:19 by vlaroque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_itoa(int n)
{
	char	neg;
	char	*nbr;
	int		len;

	neg = 0;
	len = ft_nbrlen(n);
	if (n < 0)
		neg = 1;
	if (n == 0)
		len = 1;
	if (!(nbr = ft_strnew(len + neg)))
		return (NULL);
	if (n < 0)
	{
		nbr[0] = '-';
		nbr[(len--) + neg - 1] = -(n % 10) + '0';
		n = -(n / 10);
	}
	while (--len > -1)
	{
		nbr[len + neg] = n % 10 + '0';
		n = n / 10;
	}
	return (nbr);
}
