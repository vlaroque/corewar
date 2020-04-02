/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaroque <vlaroque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 12:14:20 by vlaroque          #+#    #+#             */
/*   Updated: 2018/11/22 12:52:39 by vlaroque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_sqrt(int nbr)
{
	long long	root;

	if (nbr < 0)
		return (0);
	root = 0;
	while (root * root <= (long long)nbr)
	{
		if (root * root == nbr)
			return (root);
		root++;
	}
	return (0);
}
