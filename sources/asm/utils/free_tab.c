/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tab.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljigmon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 19:07:18 by aljigmon          #+#    #+#             */
/*   Updated: 2020/06/21 19:59:32 by aljigmon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_bool	throw_const_error(char *str)
{
	if (*str == '-' || *str == '+')
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (TRUE);
		str++;
	}
	return (FALSE);
}

void	*free_tab(char ***tab)
{
	int		i;

	i = 0;
	while ((*tab)[i])
	{
		ft_strdel(&(*tab)[i]);
		i++;
	}
	free(*tab);
	*tab = NULL;
	return (NULL);
}
