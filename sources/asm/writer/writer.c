/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   writer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljigmon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 17:05:59 by aljigmon          #+#    #+#             */
/*   Updated: 2020/07/10 11:20:46 by aljigmon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_bool					throw_fields(char *name, char *comment)
{
	if (!name)
		display_missing_field(NAME_CMD_STRING);
	else if (!comment)
		display_missing_field(COMMENT_CMD_STRING);
	else
	{
		if (ft_strlen(name) > PROG_NAME_LENGTH)
		{
			ft_putstr(".name size exceeds expected\n");
			return (TRUE);
		}
		if (ft_strlen(comment) > COMMENT_LENGTH)
		{
			ft_putstr(".comment size exceeds expected\n");
			return (TRUE);
		}
		return (FALSE);
	}
	return (TRUE);
}

static inline t_bool	is_s_ext(char *path)
{
	uint32_t	offset;

	offset = 0;
	while (*(path + offset))
		offset++;
	if (offset < 2)
		return (FALSE);
	return (!ft_strcmp(path + offset - 2, ".s"));
}

static inline size_t	get_ext_len(char *path)
{
	char		*ext;
	char		*end;

	ext = path;
	while (*ext)
		ext++;
	end = ext;
	while (ext != path && *ext != '.')
		ext--;
	return (ext == path ? 0 : (size_t)(end - ext));
}

static inline char		*get_out_file(char *in_file)
{
	size_t		src_len;
	size_t		ext_len;
	size_t		dst_len;
	char		*out_file;

	ext_len = is_s_ext(in_file) ? get_ext_len(in_file) : 0;
	src_len = ft_strlen(in_file) - ext_len;
	dst_len = src_len + 4;
	out_file = (char*)malloc(sizeof(char) * (dst_len + 1));
	if (!out_file)
		return (NULL);
	ft_strncpy(out_file, in_file, src_len);
	ft_strcpy(out_file + src_len, ".cor");
	return (out_file);
}

void					write_binary(char *in_file, t_token *token)
{
	char		*out_file;

	out_file = get_out_file(in_file);
	if (!out_file)
		return (display_filename_error(in_file));
	assemble(out_file, token);
	free(out_file);
}
