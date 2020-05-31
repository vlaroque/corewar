/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaroque <vlaroque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 17:56:00 by vlaroque          #+#    #+#             */
/*   Updated: 2020/03/10 18:13:57 by vlaroque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "corewar.h"

int			err(char *s)
{
	printf("%s\n", s);
	return (0);
}

void		char_hexa(t_octet c)
{
	char	base[] = "0123456789abcdef";

	write(1, &base[c / 16], 1);
	write(1, &base[c % 16], 1);
}

void		hex_dump(t_octet *src, size_t len)
{
	size_t		i;

	i = 0;
	while (i < len)
	{
		if (i != 0 && i % 64 == 0)
			write(1, "\n", 1);
		else if (i != 0)
			write(1, " ", 1);
		char_hexa(*src);
		src++;
		i++;
	}
	write(1, "\n", 1);
}

//128 64 32 16 8 4 2 1

int			champ_dump(t_champ *champ)
{
	if (!champ)
		return (-1);
	ft_putstr("champ id =|");
	ft_putstr(ft_itoa(champ->id));
	ft_putstr("|\nNAME = |");
	ft_putstr((char *)champ->prog_name);
	ft_putstr("|\nCOMMENT = |");
	ft_putstr((char *)champ->comment);
	ft_putstr("|\nCHAMPION");
	hex_dump(champ->content, CHAMP_MAX_SIZE);
	ft_putstr("|\n");
	return (0);
}

int			is_pointed(t_data *data, unsigned int pc)
{
	t_process	*process;

	process = data->processes;
	while (process)
	{
		if (process->pc == pc)
			return (1);
		process = process->next;
	}
	return (0);
}

int			show_mars(t_data *data)
{
	int		i;

	i = 0;
	write(1, "\e[H", 3);
	write(1, "\e[?25l", 6);
	while (i < MEM_SIZE)
	{
		if (is_pointed(data, i))
			write(1, "\e[1m", 5);
		if (i != 0 && i % 64 == 0)
			write(1, "\n", 1);
		else if (i != 0)
			write(1, " ", 1);
		char_hexa(data->mars[i]);
		write(1, "\e[0m", 5);
		i++;
	}
	write(1, "\n", 1);
	return (0);
}


void		char_hexa_str(t_octet c, char *str)
{
	char	base[] = "0123456789abcdef";

	str[0] = base[c / 16];
	str[1] = base[c % 16];
	str[2] = '\0';
}

int			write_in_buffer(char *buff, char *str, int i)
{
	int		a;

	a = 0;
	while (str[a])
	{
		buff[i + a] = str[a];
		a++;
	}
	return (i + a);
}

void		processes(t_process *p)
{
	while (p)
	{
		printf("process ptr = %x pc = %d               \n", (int)p, p->pc);
		p = p->next;
	}
}

void		fill_address(char *adress)
{
	static int adress_nbr = 0;
	char	base[] = "0123456789abcdef";

	adress[0] = '0';
	adress[1] = 'x';
	adress[2] = base[(adress_nbr / 4096) % 16];
	adress[3] = base[(adress_nbr / 256) % 16];
	adress[4] = base[(adress_nbr / 16) % 16];
	adress[5] = base[adress_nbr % 16];
	adress[6] = ' ';
	adress[7] = ':';
	adress[8] = ' ';
	adress[9] = '\0';
	adress_nbr += 64;
}

int			dump_option_mars(t_data *data)
{
	int		i;
	int		buff_i;
	char	tmp[3];
	char	adress[10];
	char	buff[MEM_SIZE * 10];

	i = 0;
	buff_i = 0;
	while (i < MEM_SIZE)
	{
		if (i % 64 == 0)
		{
			fill_address(adress);
			buff_i = write_in_buffer(buff, adress, buff_i);
		}
		char_hexa_str(data->mars[i], tmp);
		buff_i = write_in_buffer(buff, tmp, buff_i);
		buff[buff_i++] = ' ';
		if (i % 64 == 63)
			buff[buff_i++] = '\n';
		i++;
	}
	buff[buff_i] = '\0';
	write(1, buff, ft_strlen(buff));
	return (0);
}

/*
 ** colors 1 yellow 2 blue 3 red 4 green 
 */

int			color_octet(t_data *data, char *buff, int buff_i, int i)
{
	if (i == 0)
	{
		if (data->colors[i] == 1)
			buff_i = write_in_buffer(buff, "\e[93m", buff_i);
		else if (data->colors[i] == 2)
			buff_i = write_in_buffer(buff, "\e[96m", buff_i);
		else if (data->colors[i] == 3)
			buff_i = write_in_buffer(buff, "\e[91m", buff_i);
		else if (data->colors[i] == 3)
			buff_i = write_in_buffer(buff, "\e[92m", buff_i);
	}
	else if (data->colors[i - 1] != data->colors[i])
	{
		if (data->colors[i] == 0)
			buff_i = write_in_buffer(buff, "\e[39m", buff_i);
		else if (data->colors[i] == 1)
			buff_i = write_in_buffer(buff, "\e[93m", buff_i);
		else if (data->colors[i] == 2)
			buff_i = write_in_buffer(buff, "\e[96m", buff_i);
		else if (data->colors[i] == 3)
			buff_i = write_in_buffer(buff, "\e[91m", buff_i);
		else if (data->colors[i] == 3)
			buff_i = write_in_buffer(buff, "\e[92m", buff_i);
	}
	return (buff_i);
}

int			buff_mars(t_data *data)
{
	int		i;
	int		buff_i;
	char	tmp[3];
	char	buff[MEM_SIZE * 10];

	i = 0;
	buff_i = 0;
	write(1, "\e[H", 3);
	//	write_in_buffer(buff, "\e[H", buff_i);
	//	write(1, "\[?25l", 6);
	while (i < MEM_SIZE)
	{
		if (i != 0 && i % 64 == 0)
			buff[buff_i++] = '\n';
		else if (i != 0)
			buff[buff_i++] = ' ';
		buff_i = color_octet(data, buff, buff_i, i);
		if (is_pointed(data, i))
			buff_i = write_in_buffer(buff, "\e[7m", buff_i);
		//buff_i = write_in_buffer(buff, "\e[1m", buff_i);
		char_hexa_str(data->mars[i], tmp);
		buff_i = write_in_buffer(buff, tmp, buff_i);
		if (is_pointed(data, i))
			buff_i = write_in_buffer(buff, "\e[0m", buff_i);
		buff_i = color_octet(data, buff, buff_i, i);
		i++;
	}
	buff[buff_i] = '\0';
	write(1, buff, ft_strlen(buff));
	write(1, "\n", 1);
	return (0);
}
