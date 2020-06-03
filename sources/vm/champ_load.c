/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   champ_load.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaroque <vlaroque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 14:52:08 by vlaroque          #+#    #+#             */
/*   Updated: 2020/01/28 20:57:52 by vlaroque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "op.h"
#include "corewar.h"

unsigned int		big_little_endian(unsigned int nbr)
{
	unsigned int	new;
	t_octet			*ptr_nbr;
	t_octet			*ptr_new;

	ptr_nbr = (t_octet *) &nbr;
	ptr_new = (t_octet *) &new;
	ptr_new[0] = ptr_nbr[3];
	ptr_new[1] = ptr_nbr[2];
	ptr_new[2] = ptr_nbr[1];
	ptr_new[3] = ptr_nbr[0];
	return (new);
}

int		champ_fill(t_champ *champ, int fd)
{
	t_octet			tmp[4];

	if (4 != read(fd, tmp, 4))
		return (-1);
//	if (*(unsigned int *)tmp != big_little_endian(COREWAR_EXEC_MAGIC))
////		return (-2);
	if (PROG_NAME_LENGTH != read(fd, champ->prog_name, PROG_NAME_LENGTH))
		return (-3);
	if (4 != read(fd, tmp, 4))
		return (-1);
	if (4 != read(fd, tmp, 4))
		return (-1);
	champ->prog_size = big_little_endian(*(int *)(tmp));
	if (COMMENT_LENGTH != read(fd, champ->comment, COMMENT_LENGTH))
		return (-3);
	if (4 != read(fd, tmp, 4))
		return (-1);
	if (champ->prog_size != read(fd, champ->content, CHAMP_MAX_SIZE))
		return (-3);
	return (0);
}

int		what_id(t_champid *champ_id)
{
	if (champ_id->carry == 1)
	{
		champ_id->carry = 0;
		return (champ_id->carried_nbr);
	}
	else
	{
		champ_id->id++;
		return (champ_id->id - 1);
	}
}

int		new_champ(t_data *data, char *source, t_champid *champ_id)
{
	int		fd;
	t_champ	*champ;
	t_champ	*last;

	fd = open(source, O_RDONLY);
	if (fd <= 0)
		return (-1);
	if (!(champ = (t_champ *)malloc(sizeof(t_champ))))
		return (-1);
	data->nbr_champs++;
	op_bzero(champ, sizeof(t_champ));
	champ->id = what_id(champ_id);
	data->last_alive = champ->id;
	if (!data->champs)
		data->champs = champ;
	else
	{
		last = data->champs;
		while (last->next)
			last = last->next;
		last->next = champ;
	}
	champ_fill(champ, fd);
	close(fd);
	return (1);
}
