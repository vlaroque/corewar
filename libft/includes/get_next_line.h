/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaroque <vlaroque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 15:30:25 by vlaroque          #+#    #+#             */
/*   Updated: 2018/12/03 12:35:48 by vlaroque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFF_SIZE 100

typedef struct s_buff	t_buff;

struct					s_buff
{
	int		fd;
	char	*buff;
	int		buff_size;
	t_buff	*next;
};

int						get_next_line(const int fd, char **line);

#endif
