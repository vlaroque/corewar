/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stherkil <stherkil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 17:02:22 by stherkil          #+#    #+#             */
/*   Updated: 2020/02/19 15:21:58 by stherkil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm.h"

static int		findlastpt(char *addr)
{
	int		len;
	char	*cpyaddr;

	cpyaddr = NULL;
	len = ft_strlen(addr);
	while (--len)
		if (addr[len - 1] == '.')
			break ;
	return (len);
}

static void		partone(unsigned char *BUF, int *bufptout, header_t *header)
{
	int		bufpt;

	bufpt = *bufptout;
	itobh(BUF, &bufpt, COREWAR_EXEC_MAGIC);
	ft_memcpy(BUF + bufpt, header->prog_name, ft_strlen(header->prog_name) - 1);
	bufpt += ft_strlen(header->prog_name) - 1;
	ft_bzero(BUF + bufpt, PROG_NAME_LENGTH - ft_strlen(header->prog_name) + 5);
	bufpt += PROG_NAME_LENGTH - ft_strlen(header->prog_name) + 5;
	itobh(BUF, &bufpt, header->tot_len);
	ft_memcpy(BUF + bufpt, header->comment, ft_strlen(header->comment));
	bufpt += ft_strlen(header->comment);
	ft_bzero(BUF + bufpt, COMMENT_LENGTH - ft_strlen(header->comment) + 4);
	bufpt += COMMENT_LENGTH - ft_strlen(header->comment) + 4;
	*bufptout = bufpt;
}

static void		asmtofile(header_t *header, char *name1)
{
	unsigned char	BUF[3000];
	int				fd;
	char			*name2;
	int				bufpt;

	if (findlastpt(name1) == ft_strlen(name1))
		errorparser("Writing output program to .cor", header);
	if (!(name2 = ft_strndup(name1, findlastpt(name1) + 3)))
		errorparser("MALLOC ERROR", header);
	ft_strcpy(name2 + findlastpt(name1), "cor");
	fd = open(name2, O_CREAT | O_RDWR, 0644);
	partone(BUF, &bufpt, header);
	parttwo(BUF, &bufpt, header);
	printf("bufpt is %d\n", bufpt);
	write(fd, BUF, bufpt);
	free(name2);
	close(fd);
}

int				main(int argc, char **argv)
{
	header_t	*header;

	header = NULL;
	header = malloc(sizeof(header_t));
	if (argc != 2)
		errorparser("Usage: ./asm [-a] <sourcefile.s>\n -a : Instead of creating a .cor file, outputs a stripped and annotated version of the code to the standard output", header);
	if ((header->fd = open(argv[1], O_RDONLY)) < 0)
	{
		ft_putstr("Can't read source file ");
		errorparser(argv[1], header);
	}
	asmparsing(header);
	printf("len is %d\n", header->tot_len);
	close(header->fd);
	asmtofile(header, argv[1]);
	return (0);
}
