/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_power.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaroque <vlaroque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 20:00:14 by vlaroque          #+#    #+#             */
/*   Updated: 2018/11/21 20:51:47 by vlaroque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_power(int nbr, int pwr)
{
	long int	result;

	result = nbr;
	if (pwr < 0)
		return (0);
	if (pwr == 0)
		return (0);
	if (pwr == 1)
		return (nbr);
	while (--pwr)
	{
		if (!(result * nbr <= 2147483647) || (result * nbr >= 2147483648))
			return (0);
		result = result * nbr;
	}
	return ((int)result);
}
