/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_parsing_head.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stherkil <stherkil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 14:37:08 by stherkil          #+#    #+#             */
/*   Updated: 2020/02/19 15:28:37 by stherkil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm.h"

static void getparam(header_t *header, char *s, char *str, char *dest)
{
	int i;
	int collen;

	i = -1;
	s = s + (collen = ft_strchlen(str, COMMENT_CHAR));
	while (*s && *s <= ' ' && ++header->col)
		s++;
	header->col += collen;
	if (*s != '\"')
		errorparserasm(ft_strndup(s, ft_strchlen(s, '\"')), header, 1, 1);
	while (s[++i])
		if (s[i] == '\"')
			break ;
	if (s[i] != '\"')
		errorparserasm("", header, 1, 0);
	ft_strncpy(dest, s + 1, (i = ft_strchlen(s + 1, '\"')));
	s = s + i + 2;
	while (*s)
	{
		if (*s > ' ')
			errorparserasm("", header, 1, 0);
		s++;
	}
}

void	asmparsehead(header_t *header)
{
	char *s;

	header->col = 1;
	s = skipnl(header);
	if (ft_strncmp(NAME_CMD_STRING, s, ft_strchlen(NAME_CMD_STRING, COMMENT_CHAR)))
		errorparserasm("", header, 3, 0);
	getparam(header, s, NAME_CMD_STRING, header->prog_name);
	free(s);
	s = skipnl(header);
	if (ft_strncmp(COMMENT_CMD_STRING, s, ft_strchlen(COMMENT_CMD_STRING, COMMENT_CHAR)))
		errorparserasm("", header, 3, 0);
	getparam(header, s, COMMENT_CMD_STRING, header->comment);
	printf("magic nb %d\n", COREWAR_EXEC_MAGIC);
	free(s);
}
