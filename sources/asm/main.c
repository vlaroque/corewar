/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljigmon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 12:00:53 by aljigmon          #+#    #+#             */
/*   Updated: 2020/06/20 21:24:43 by aljigmon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		main(int ac, char **av)
{
	int			fd;
	t_token		*tokens;

	if (ac != 2)
	{
		ft_putstr("Usage: ./asm <file.s>\n");
		exit(EXIT_FAILURE);
	}
	fd = open(av[1], O_RDONLY);
	if (fd == ERROR)
	{
		ft_putstr("Can't read source file, does ");
		ft_putstr(av[1]);
		ft_putstr(" exist ?\n");
		exit(EXIT_FAILURE);
	}
	tokens = parser((const int)fd);
	if (!tokens)
	{
		free_tokens(&tokens);
		exit(EXIT_FAILURE);
	}
	write_binary(av[1], tokens);
	close(fd);
	exit(EXIT_SUCCESS);
}
