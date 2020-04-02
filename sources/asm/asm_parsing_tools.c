/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_parsing_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stherkil <stherkil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 11:01:42 by stherkil          #+#    #+#             */
/*   Updated: 2020/02/19 14:57:15 by stherkil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int checkclean(char *s)
{
	int i;

	i = -1;
	while (++i < ft_strlen(s))
	{
		if (s[i] == COMMENT_CHAR)
			break ;
		else if (s[i] > ' ')
			return (0);
	}
	return (1);
}

char *skipnl(header_t *header)
{
	char *s;
	int ret;

	while ((ret = get_next_line(header->fd, &s)))
	{
		++header->row;
		if (s && s[0] && !checkclean(s))
			break ;
		free(s);
	}
	if (ret <= 0)
		return (NULL);
	return (s);
}