/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaroque <vlaroque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 19:22:45 by vlaroque          #+#    #+#             */
/*   Updated: 2018/11/22 16:31:13 by vlaroque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static void		ft_delete(void *content, size_t content_size)
{
	free(content);
	(void)content_size;
}

t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list		*tmp;
	t_list		*prevtmp;
	t_list		*save;

	if (lst == NULL || f == NULL)
		return (NULL);
	save = NULL;
	while (lst)
	{
		if (!(tmp = f(lst)))
		{
			if (save)
				ft_lstdel(&save, &ft_delete);
			return (NULL);
		}
		lst = lst->next;
		if (save)
			prevtmp->next = tmp;
		prevtmp = tmp;
		if (!save)
			save = tmp;
	}
	prevtmp->next = NULL;
	return (save);
}
