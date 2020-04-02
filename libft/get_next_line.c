/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaroque <vlaroque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 19:42:39 by vlaroque          #+#    #+#             */
/*   Updated: 2018/12/06 09:25:07 by vlaroque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"
#include <unistd.h>
#include <stdlib.h>

t_buff	*ft_fd_s_chain(int fd)
{
	static t_buff	*prem_elem;
	t_buff			*work_elem;

	work_elem = prem_elem;
	while (work_elem)
	{
		if (work_elem->fd == fd)
			return (work_elem);
		work_elem = work_elem->next;
	}
	if (!(work_elem = (t_buff *)malloc(sizeof(t_buff))))
		return (NULL);
	work_elem->next = prem_elem;
	work_elem->fd = fd;
	work_elem->buff = NULL;
	work_elem->buff_size = 0;
	prem_elem = work_elem;
	return (prem_elem);
}

int		ft_read_first_time(t_buff *fd_ch)
{
	if (fd_ch->buff_size == 0)
	{
		if (!(fd_ch->buff = ft_strnew(BUFF_SIZE)))
			return (-1);
		fd_ch->buff_size = read(fd_ch->fd, fd_ch->buff, BUFF_SIZE);
		if (fd_ch->buff_size == -1)
			return (-1);
	}
	return (0);
}

int		ft_read_or_not(t_buff *fd_ch, char **line, char *tmp, char *tmp2)
{
	char		*endstr;

	if ((endstr = ft_strchr(fd_ch->buff, '\n')))
	{
		*line = ft_strsub(fd_ch->buff, 0, endstr - fd_ch->buff);
		tmp = fd_ch->buff;
		if (!(fd_ch->buff = ft_strdup(endstr + 1)))
			return (-1);
		free(tmp);
		return (1);
	}
	tmp = fd_ch->buff;
	if (!(tmp2 = ft_strnew(BUFF_SIZE)))
		return (-1);
	if ((fd_ch->buff_size = read(fd_ch->fd, tmp2, BUFF_SIZE)) == -1)
	{
		free(tmp2);
		return (-1);
	}
	fd_ch->buff = ft_strjoin(tmp, tmp2);
	free(tmp);
	free(tmp2);
	*line = NULL;
	return (0);
}

int		get_next_line(const int fd, char **line)
{
	t_buff		*fd_ch;
	int			ret;

	fd_ch = ft_fd_s_chain(fd);
	if (ft_read_first_time(fd_ch) == -1)
		return (-1);
	while (42)
	{
		if (fd_ch->buff_size == 0)
		{
			if (ft_strlen(fd_ch->buff))
			{
				if (!(*line = ft_strdup(fd_ch->buff)))
					return (-1);
				free(fd_ch->buff);
				fd_ch->buff = NULL;
				fd_ch->buff_size = 0;
				return (1);
			}
			return (0);
		}
		if ((ret = ft_read_or_not(fd_ch, line, NULL, NULL)) != 0)
			return (ret);
	}
}
