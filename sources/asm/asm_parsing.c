/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stherkil <stherkil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 11:01:42 by stherkil          #+#    #+#             */
/*   Updated: 2020/02/19 17:29:03 by stherkil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm.h"

void headerinit(header_t *header)
{
	if (!(header->instr = malloc(sizeof(instr_t))))
		errorparser("malloc error", header);
	header->labels = NULL;
	header->firstinstr = header->instr;
	header->instr->next = NULL;
	header->lastlabelnb = 0;
	header->tot_len = 0;
	header->col = 0;
	header->row = 0;
	header->par = 0;

}

void	asmparsing(header_t *header)
{
	//unsigned char	BUF[2192];
	char *s;
	int ret;

	s = NULL;
	ret = 0;
	headerinit(header);
	asmparsehead(header);
	asmparseinstr(header);
	instr_t *check = header->firstinstr;

	printf("name is @%s@\n", header->prog_name);
	printf("comment is @%s@\n", header->comment);

	while ((check->instr != -1))
	{
		printf("instr nb val%d data: %d %d %d\n", check->instr, check->data[0], check->data[1], check->data[2]);
		check = check->next;
	}
	/*
	   first instruct
	   */
}
