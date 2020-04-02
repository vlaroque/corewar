/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stherkil <stherkil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 17:02:22 by stherkil          #+#    #+#             */
/*   Updated: 2020/02/19 15:46:33 by stherkil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm.h"

void	errorparser(const char *s, header_t *header)
{
	if (header)
		free(header);
	ft_putendl(s);
	exit(0);
}

static void	printrowcol(header_t *header, int mode)
{
	write(1, "[", 1);
	if (!(header->row / 100) && mode == 0)
		ft_putchar('0');
	if (!(header->row / 10) && mode == 0)
		ft_putchar('0');
	ft_putnbr(header->row);
	write(1, ":", 1);
	if (!(header->col / 100) && mode == 0)
		ft_putchar('0');
	if (!(header->col / 10) && mode == 0)
		ft_putchar('0');
	ft_putnbr(header->col);
	write(1, "]", 1);
}

void	errorparserasm(char *s, header_t *header, int errtyp, int freestr)
{
	if (errtyp == 0)
	{
		write(1, "Invalid parameter ", 18);
		ft_putchar('0' + header->par);
		write(1, " type register for instruction ", 31);
	}
	else if (errtyp == 1 || errtyp == 2)
	{
		write(1, "Syntax error at token [TOKEN]", 29);
		printrowcol(header, 0);
		if (errtyp == 1)
			write(1, " INSTRUCTION ", 13);
		else
			write (1, " END \"(null)\"", 15);
	}
	if (errtyp == 3)
	{
		write(1, "Lexical error at ", 17);
		printrowcol(header, 1);
	}
	if (freestr)
		free(s);
	ft_putendl(s);
	if (header)
		free(header);
	exit(0);
}