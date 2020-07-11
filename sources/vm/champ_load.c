/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   champ_load.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaroque <vlaroque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 14:52:08 by vlaroque          #+#    #+#             */
/*   Updated: 2020/07/10 22:04:49 by vlaroque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "op.h"
#include "corewar.h"

int				big_little_endian(int nbr)
{
	unsigned int	new;
	t_octet			*ptr_nbr;
	t_octet			*ptr_new;

	ptr_nbr = (t_octet *)&nbr;
	ptr_new = (t_octet *)&new;
	ptr_new[0] = ptr_nbr[3];
	ptr_new[1] = ptr_nbr[2];
	ptr_new[2] = ptr_nbr[1];
	ptr_new[3] = ptr_nbr[0];
	return (new);
}

static int		champ_fill(t_data *data, t_champ *champ, int fd)
{
	t_octet			tmp[4];

	if (4 != read(fd, tmp, 4))
		print_error(data, 20);
	if (*(int *)tmp != big_little_endian(COREWAR_EXEC_MAGIC))
		print_error(data, 21);
	if (PROG_NAME_LENGTH != read(fd, champ->prog_name, PROG_NAME_LENGTH))
		print_error(data, 20);
	if (4 != read(fd, tmp, 4))
		print_error(data, 20);
	if (4 != read(fd, tmp, 4))
		print_error(data, 20);
	champ->prog_size = big_little_endian(*(int *)(tmp));
	if (champ->prog_size > CHAMP_MAX_SIZE)
		print_error(data, 22);
	if (COMMENT_LENGTH != read(fd, champ->comment, COMMENT_LENGTH))
		print_error(data, 20);
	if (4 != read(fd, tmp, 4))
		print_error(data, 20);
	if (champ->prog_size != read(fd, champ->content, CHAMP_MAX_SIZE))
		print_error(data, 20);
	return (0);
}

static int		id_exist(t_data *data, int id)
{
	t_champ		*champ;

	champ = data->champs;
	while (champ)
	{
		if (champ->n_option && champ->id == id)
			return (1);
		champ = champ->next;
	}
	return (0);
}

static int		what_id(t_data *data, t_champ *champ, t_champid *champ_id)
{
	if (champ_id->carry == 1)
	{
		if (id_exist(data, champ_id->carried_nbr))
		{
			close(data->fd);
			print_error(data, 40);
		}
		champ_id->carry = 0;
		champ->id = champ_id->carried_nbr;
		champ->n_option = 1;
	}
	return (0);
}

int				new_champ(t_data *data, char *source, t_champid *champ_id)
{
	t_champ		*champ;
	t_champ		*last;

	data->fd = open(source, O_RDONLY);
	if (data->fd < 1)
		print_error(data, -2);
	if (!(champ = (t_champ *)malloc(sizeof(t_champ))))
		close(data->fd);
	if (!(champ))
		print_error(data, -1);
	data->nbr_champs++;
	op_bzero(champ, sizeof(t_champ));
	what_id(data, champ, champ_id);
	if (!data->champs)
		data->champs = champ;
	else
	{
		last = data->champs;
		while (last->next)
			last = last->next;
		last->next = champ;
	}
	champ_fill(data, champ, data->fd);
	close(data->fd);
	return (1);
}
