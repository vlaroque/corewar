/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freechartab.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaroque <vlaroque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 18:43:00 by vlaroque          #+#    #+#             */
/*   Updated: 2018/11/21 19:15:03 by vlaroque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void		ft_freechartab(char ***tab)
{
	size_t	i;

	i = 0;
	while ((*tab)[i])
		free((*tab)[i++]);
	free(*tab);
	*tab = NULL;
}
