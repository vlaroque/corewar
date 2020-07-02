/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljigmon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 14:47:34 by aljigmon          #+#    #+#             */
/*   Updated: 2020/06/21 20:07:31 by aljigmon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "asm_structures.h"

char	*read_file(const int fd);
void	*free_tab(char ***tab);
char	**del_useless(char const *s);

#endif
