/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaroque <vlaroque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 14:59:43 by vlaroque          #+#    #+#             */
/*   Updated: 2018/11/24 11:40:55 by vlaroque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list		*ft_lstnew(void const *content, size_t content_size)
{
	t_list			*tmp;
	unsigned char	*str;
	int				i;

	if (!(tmp = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	if (content == NULL || content_size == 0)
	{
		tmp->content = NULL;
		tmp->content_size = 0;
	}
	else if ((i = -1) == -1)
	{
		if (!(str = (unsigned char *)malloc(sizeof(char) * (content_size))))
		{
			free(tmp);
			return (NULL);
		}
		while (++i < (int)content_size)
			str[i] = ((unsigned char *)content)[i];
		tmp->content = (void *)str;
		tmp->content_size = content_size;
	}
	tmp->next = NULL;
	return (tmp);
}
