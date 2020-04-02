/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaroque <vlaroque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 14:31:42 by vlaroque          #+#    #+#             */
/*   Updated: 2018/11/24 11:41:22 by vlaroque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_lstdel(t_list **alst, void (*del)(void*, size_t))
{
	t_list	**tmporigin;
	t_list	*tmp;

	if (alst == NULL || *alst == NULL)
		return ;
	tmporigin = alst;
	while (*alst)
	{
		del((*alst)->content, (*alst)->content_size);
		tmp = *alst;
		(*alst) = (*alst)->next;
		free(tmp);
	}
	*tmporigin = NULL;
}
