/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljigmon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 17:04:29 by aljigmon          #+#    #+#             */
/*   Updated: 2020/06/22 17:04:51 by aljigmon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_file		*init_file(void)
{
	t_file	*file;

	file = (t_file*)malloc(sizeof(t_file));
	if (!file)
		return (NULL);
	file->fd = -1;
	file->buffer = (char*)malloc(sizeof(char) * 4096);
	if (!file->buffer)
	{
		free(file);
		return (NULL);
	}
	file->page = 1;
	file->size = 0;
	return (file);
}

int			load_file(t_file *file, char *filename)
{
	file->fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	return (file->fd);
}

void		file_flush(t_file *file)
{
	if (file->fd == -1)
		return ;
	write(file->fd, file->buffer, file->size);
	file->size = 0;
}

void		write_buffer(t_file *file, char *data, uint32_t size)
{
	uint32_t	current_size;

	if (!file->buffer)
		return ;
	current_size = file->page * 4096;
	if (file->size > current_size)
	{
		file->buffer = (char*)realloc(file->buffer,
				(sizeof(char)) * (file->size + 4096));
		file->page++;
	}
	if (file->buffer)
		ft_memcpy(file->buffer + file->size, data, size);
	file->size += size;
}

void		clear_file(t_file *file)
{
	if (file->fd != -1)
		close(file->fd);
	if (file->buffer)
		free(file->buffer);
	free(file);
}
